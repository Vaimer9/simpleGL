#include "logger.hpp"
#include <utils.hpp>
#include <window.hpp>
#include <glm/vec2.hpp>
#include <string>

namespace sgl {

Window::Window(std::string title, int w, int h, bool init):
    title_(title), width_(w), height_(h), handle_(nullptr)
{
    if (init)
    {
        this->init();
    }
}

void Window::loop(std::function<void()> func)
{
    log_info("Starting main loop");
    while (!this->get_key(exit_key_) && !this->should_close())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);

        func();

        this->swap_buffers();
        this->poll_events();
    }
}

void Window::set_exit_key(int key)
{
    exit_key_ = key;
}

bool Window::should_close()
{
    return glfwWindowShouldClose(handle_);
}

GLFWwindow* Window::handle()
{
    return handle_;
}

Window::~Window()
{
    glfwDestroyWindow(handle_);
}

bool Window::get_key(int key)
{
    return glfwGetKey(handle_, key);
}

glm::vec2 Window::get_mouse_location()
{
    double x, y;
    glfwGetCursorPos(handle_, &x, &y);
    return glm::vec2(x, y);
}

void Window::set_mouse_location(glm::vec2 loc)
{
    glfwSetCursorPos(handle_, loc.x, loc.y);
}

void Window::init()
{
    log_info("Initializing Window of " + std::to_string(width_) + "x" + std::to_string(height_));
    handle_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
    if (!handle_)
    {
        log_error("Failed to create GLFW window");
        glfwTerminate();
        exit_sgl();
    }
    glfwMakeContextCurrent(handle_);
    glfwSwapInterval(1);

    glViewport(0, 0, width_, height_);
    glfwSetFramebufferSizeCallback(handle_, framebuffer_size_callback);
    glfwSwapInterval(1);

    // This fits more in sgl::init() but if taken out sgl stops working
    // Problematic when creating multiple windows 
    if (glewInit() != GLEW_OK)
    {
        log_error("Could not initialize GLew");
        exit_sgl();
    }
}

void Window::swap_buffers() 
{
    glfwSwapBuffers(handle_);
}

}
