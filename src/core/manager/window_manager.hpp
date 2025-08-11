#pragma once
#include "core/globals.hpp"

namespace core {
    class WindowManager
    {
    private:
        GLFWwindow *mpWindow;
        
    public:
        WindowManager() { mpWindow = NULL; };
        ~WindowManager() { };
        
        void createWindow(int width, int height);
        GLFWwindow* getWindow();
        
        bool isRunning();
        float getProcessTime();
        void destroyWindow();
    };
}
