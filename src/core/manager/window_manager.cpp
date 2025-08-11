#include "window_manager.hpp"
#include <filesystem>
#include <iostream>

namespace core {
    void WindowManager::createWindow(int width, int height)
    {
        if (!glfwInit()) {
            std::cout << "Failed to initialise GLFW" << std::endl;
            return;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        
        // Without these two hints, nothing above OpenGL version 2.1 is supported
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        std::cout << "Creating window ..." << std::endl;
        GLFWwindow *pWindow = glfwCreateWindow(width, height, PROGRAM_NAME, NULL, NULL);
        
        if (pWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            mpWindow = pWindow;
            return;
        }
        
        glfwMakeContextCurrent(pWindow);
        
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            mpWindow = pWindow;
            return;
        }
        
        glfwMakeContextCurrent(pWindow);
        glfwSetFramebufferSizeCallback(pWindow,
                                       []([[maybe_unused]] GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        });
        
        glfwMakeContextCurrent(pWindow);
        
        std::cout << "Setting draw methods..." << std::endl;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        
        std::cout << "Resizing display..." << std::endl;
        glfwGetFramebufferSize(pWindow, &width, &height);
        glViewport(0, 0, width, height);
        
        std::cout << "Setup complete, proceeding to main loop.\n" << std::endl;
        
        mpWindow = pWindow;
    }
    
    GLFWwindow* WindowManager::getWindow() {
        return mpWindow;
    }
    
    bool WindowManager::isRunning() {
        return !glfwWindowShouldClose(mpWindow);
    }
    
    float WindowManager::getProcessTime() {
        return glfwGetTime();
    }
    
    void WindowManager::destroyWindow() {
        glfwDestroyWindow(mpWindow);
    }
}
