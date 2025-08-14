#include "core/manager/window_manager.hpp"
#include "audio/audio_capture.hpp"
#include "render/manager/render_manager.hpp"
#include "render/audio_visualizer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>

namespace core {
    std::vector<float> visualBuffer;
    std::mutex visualMutex;
    
    void audioDataCallback(const float* data, size_t numFrames) {
        std::lock_guard<std::mutex> lock(visualMutex);
        visualBuffer.assign(data, data + numFrames);
    }

    int run()
    {
        WindowManager windowManager = WindowManager();
        windowManager.createWindow(800, 600);
        
        if(windowManager.getWindow() == NULL) {
            exit(1);
            return 1;
        }
        
        render::RenderManager renderManager = render::RenderManager(
                                                         windowManager,
                                                         "res/shaders/vertex_shader.vs",
                                                         "res/shaders/fragment_shader.fs"
                                                     );

        // Initialize audio capture
        audio::AudioCapture audio;
        if (!audio.initialize(44100, 1024)) {
            std::cerr << "Failed to initialize audio capture" << std::endl;
            return -1;
        } else {
            std::cout << "Audio capture initialized successfully" << std::endl;
        }

        
        // Set the audio callback
        audio.setCallback(audioDataCallback);

        if (!audio.start()) {
            std::cerr << "Failed to start audio capture" << std::endl;
            return -1;
        } else {
            std::cout << "Audio capture started successfully" << std::endl;
        }

        while (windowManager.isRunning()) {
            {
                std::lock_guard<std::mutex> lock(visualMutex);
                if (!visualBuffer.empty()) {
                    render::AudioVisualizer::update(visualBuffer, renderManager.getAudioVisualizerDataPoints());
                }
            }

            renderManager.renderScene();
        }
        
        renderManager.cleanBuffers();
        windowManager.destroyWindow();
        glfwTerminate();
        exit(EXIT_SUCCESS);
        
        return 0;
    }
}
