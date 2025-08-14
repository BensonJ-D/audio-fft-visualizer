#include "render_manager.hpp"

#include "core/opengl.hpp"

#include "render/domain/shader.hpp"

namespace render {
    RenderManager::RenderManager(core::WindowManager& windowManager, std::string vertexShader, std::string fragmentShader, size_t audioVisualiserMaxDataPoints) : 
        mWindowManager(windowManager), mShader(vertexShader, fragmentShader), mLineMaximumDataPoints(audioVisualiserMaxDataPoints) 
    {
        generateBuffers();
        mShader.use();
    }
    void RenderManager::renderScene() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glBindVertexArray(mLineVertexArrayObj);
        glBindBuffer(GL_ARRAY_BUFFER, mLineVertexBufferObj);
        glBufferData(GL_ARRAY_BUFFER, mAudioVisualizerDataPoints.size() * sizeof(float), mAudioVisualizerDataPoints.data(), GL_STREAM_DRAW);
        glDrawArrays(GL_LINE_STRIP, 0, mAudioVisualizerDataPoints.size() / 2);
        
        glfwSwapBuffers(mWindowManager.getWindow());
        glfwPollEvents();
    }
    
    void RenderManager::cleanBuffers() {
        glDeleteVertexArrays(1, &mLineVertexArrayObj);
        glDeleteBuffers(1, &mLineVertexBufferObj);
    }
    
    
    void RenderManager::generateBuffers() {
        /* -- Audio Visualizer rendering objects -- */
        GLuint lineVertexArrayObj, lineVertexBufferObj;
        glGenVertexArrays(1, &lineVertexArrayObj);
        glGenBuffers(1, &lineVertexBufferObj);
        
        glBindVertexArray(lineVertexArrayObj);
        glBindBuffer(GL_ARRAY_BUFFER, lineVertexBufferObj);
        
        glBufferData(GL_ARRAY_BUFFER, mLineMaximumDataPoints * 2 * sizeof(float), nullptr, GL_STREAM_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        mLineVertexArrayObj = lineVertexArrayObj;
        mLineVertexBufferObj = lineVertexBufferObj;

        mAudioVisualizerDataPoints.reserve(mLineMaximumDataPoints * 2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
