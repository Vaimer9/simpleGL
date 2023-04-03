#include <string>
#include <utils.hpp>
#include <logger.hpp>

namespace sgl {

void init()
{
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    log_info("Initialied GLFW");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (float)width, (float)height, 0.0, -1.0, 1.0);
    // glMatrixMode(GL_MODELVIEW);
}

void exit_sgl()
{
    log_info("Shutting down SGL");
    exit(-1);
}

}
