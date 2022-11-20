#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace Utilities {
    GLuint get_projection_view_matrix_id();
};

GLuint load_shaders(const char* vertex_file_path, const char* fragment_file_path);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* gl_init();
