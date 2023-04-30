//
// Created by zartris on 4/25/23.
//

#pragma once
#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"

#include <string>


namespace graphics {
    class vulkanWindow {
    public:
        vulkanWindow(int width, int height, std::string windowName);

        ~vulkanWindow();

        void initWindow();

        bool shouldClose();

        // Delete the copy constructor and assignment operator
        // to prevent the window from being copied and keeping multiple instances
        vulkanWindow(const vulkanWindow &) = delete;

        vulkanWindow &operator=(vulkanWindow &&) = delete;

    private:
        const int width;
        const int height;
        const std::string windowName;
        GLFWwindow *window;
    };
} // graphics


