//
// Created by zartris on 4/25/23.
//

#include "bhs_vis/vulkanWindow.h"

namespace graphics {

// Define the vulkanWindow constructor with parameters for width, height, and windowName
    vulkanWindow::vulkanWindow(int width, int height, std::string windowName) :
            width(width), height(height), windowName(std::move(windowName)) {
        initWindow(); // Call initWindow function to initialize the window
    }

// Define the destructor for the vulkanWindow class
    vulkanWindow::~vulkanWindow() {
        glfwDestroyWindow(window); // Destroy the window
        glfwTerminate(); // Terminate GLFW
    }

// Define the initWindow function to initialize the window
    void vulkanWindow::initWindow() {
        glfwInit(); // Initialize GLFW
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Tell GLFW not to use OpenGL or any other client API
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Make the window non-resizable
        // Create the window with the specified width, height, and windowName, and store it in the window variable
        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }

// Define the shouldClose function to check if the window should close
    bool vulkanWindow::shouldClose() {
        return glfwWindowShouldClose(window); // Return true if the window should close, false otherwise
    }


}