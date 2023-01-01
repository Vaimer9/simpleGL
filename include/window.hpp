#pragma once

#include <stdlib.h>
#include <string>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* window_handle; 
    std::string window_title;
    int window_width, window_height;

public:
    Window(std::string title, int width, int height);
    
    GLFWwindow* get_handle();
    void init();
    void swap_buffers();
    ~Window();
};
