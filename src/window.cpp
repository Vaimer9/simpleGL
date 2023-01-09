#include <utils.hpp>
#include <window.hpp>

Window::Window(std::string title, int w, int h, bool init)
{
    title_ = title;
    width_ = w;
    height_ = h;
    handle_ = NULL;

    if (init)
    {
        this->init();
    }
}

void Window::loop(std::function<void()> func)
{
    while (!this->get_key(exit_key_) && !this->should_close())
    {
        glClear(GL_COLOR_BUFFER_BIT);

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

void Window::init()
{
    handle_ =
        glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
    if (!handle_)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(handle_);
    glfwSwapInterval(1);

    glViewport(0, 0, width_, height_);
    glfwSetFramebufferSizeCallback(handle_, Utilities::framebuffer_size_callback);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
        exit(-1);
    }
}

void Window::swap_buffers() 
{
    glfwSwapBuffers(handle_);
}

