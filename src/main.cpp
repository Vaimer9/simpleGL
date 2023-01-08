#include "mesh.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <window.hpp>
#include <shader.hpp>
#include <vao.hpp>
#include <vbo.hpp>

#include <utils.hpp>

int main()
{
    Utilities::glfw_init();
    Window window = Window("Opengl Window", 800, 600);
    window.init();

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
        exit(-1);
    }

    const float offset = 0.7f;

    const GLfloat g_vertex_matrix[] = { 
        -0.20f - offset, -0.5f, 0.0f, // bottom left
        0.0f - offset, -0.5f, 0.0f, // bottom right
        0.0f - offset,  0.5f, 0.0f, // top right
        -0.20f - offset, 0.5f, 0.0f, // top left
	};

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    Shader shaders = Shader("../shaders/vertex.vert", "../shaders/fragment.frag");
    shaders.load_shaders();
    shaders.use();

    ArrayBuffer vertices = ArrayBuffer(
        (void*)g_vertex_matrix,
        sizeof(g_vertex_matrix),
        GL_STATIC_DRAW
    );

    Vbo elements = Vbo(
        GL_ELEMENT_ARRAY_BUFFER,
        (void*)indices,
        sizeof(indices),
        GL_STATIC_DRAW
    );

    Vao vao = Vao(1);
    vao.bind();
    vao.add_array_buffer(
        &vertices.set_index(0)
            .set_size(3)
            .set_type(GL_FLOAT)
            .set_normalized(GL_FALSE)
            .set_stride(0)
    );
    vao.add_element_buffer(&elements);

    glm::vec2 adv = glm::vec2(0, 0);
    shaders.set_vec2("v_Pos", adv);

    vao.bind();

    Mesh rectangle = Mesh(&vao, &shaders);
    rectangle.set_vertices(6);

    float vel = 0.005f;

    do {
        glClear(GL_COLOR_BUFFER_BIT);
        shaders.set_vec2("v_Pos", adv);

        if (window.get_key(GLFW_KEY_W)) {
            adv.y += vel;
        } else if (window.get_key(GLFW_KEY_S)) {
            adv.y -= vel;
        } else if (window.get_key(GLFW_KEY_A)) {
            adv.x -= vel;
        } else if (window.get_key(GLFW_KEY_D)) {
            adv.x += vel;
        }

        rectangle.render();
        window.swap_buffers();

        Window::poll_events();
    } while (!window.get_key(GLFW_KEY_Q) && !window.should_close());

    return 0;
}
