#pragma once

#include <functional>
#include <glm/fwd.hpp>
#include <stdlib.h>
#include <string>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* handle_; 
    std::string title_;
    int width_, height_, exit_key_;
public:
    Window(std::string title, int width, int height, bool init = false);
    
    void loop(std::function<void()> func);
    GLFWwindow* handle();
    bool get_key(int key);
    bool should_close();
    void init();
    void swap_buffers();
    void set_exit_key(int key);
    glm::vec2 get_mouse_location();
    void set_mouse_location(glm::vec2 location);

    static void poll_events() {
        glfwPollEvents();
    }

    ~Window();
};
