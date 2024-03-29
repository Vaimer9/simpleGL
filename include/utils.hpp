#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

namespace sgl {

GLuint get_projection_view_matrix_id();
void init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void exit_sgl();

}
