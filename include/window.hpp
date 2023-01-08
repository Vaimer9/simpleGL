#pragma once

#include <stdlib.h>
#include <string>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* handle_; 
    std::string title_;
    int width_, height_;
public:
    Window(std::string title, int width, int height);
    
    GLFWwindow* handle();
    bool get_key(int key);
    bool should_close();
    void init();
    void swap_buffers();

    static void poll_events() {
        glfwPollEvents();
    }

    ~Window();
};
