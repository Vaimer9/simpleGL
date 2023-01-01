#include <utils.hpp>
#include <window.hpp>

Window::Window(std::string title, int w, int h)
{
    window_title = title;
    window_width = w;
    window_height = h;
    window_handle = NULL;
}

GLFWwindow* Window::get_handle()
{
    return window_handle;
}

void Window::init()
{
    window_handle =
        glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);
    if (!window_handle)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window_handle);
    glfwSwapInterval(1);

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window_handle, framebuffer_size_callback);
    glfwSwapInterval(1);
}

void Window::swap_buffers() 
{
    glfwSwapBuffers(window_handle);
}

Window::~Window()
{
    glfwDestroyWindow(window_handle);    
}
