#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/opengl.hpp"
#include "core/manager/window_manager.hpp"

#include "render/domain/shader.hpp"


namespace render {
    class RenderManager {
        private:
            core::WindowManager *mpWindowManager;        
            render::Shader mShader;
            
            GLuint mLineVertexArrayObj;
            GLuint mLineVertexBufferObj;

            size_t mLineMaximumDataPoints;
            size_t mAudioVisualizerTotalDataPoints = 0;
            
            std::vector<float> mAudioVisualizerDataPoints;
        
            void generateBuffers();
        
        public:
            RenderManager(core::WindowManager *pWindowManager, std::string vertexShader, std::string fragmentShader, size_t audioVisualiserMaxDataPoints = 2048);
            void renderScene();
            void cleanBuffers();

            std::vector<float>* getAudioVisualizerDataPointsPointer() {
                return &mAudioVisualizerDataPoints;
            }
    };
}
