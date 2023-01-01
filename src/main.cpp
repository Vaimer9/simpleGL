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
#include <config.hpp>

int main()
{
    Utilities::glfw_init();
    Window window = Window(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    window.init();

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
        exit(-1);
    }

    Vao vao = Vao(1);
    vao.bind();

    float offset = 0.7f;

    static const GLfloat g_vertex_matrix[] = { 
        -0.20f - offset, -0.5f, 0.0f, // bottom left
        0.0f - offset, -0.5f, 0.0f, // bottom right
        0.0f - offset,  0.5f, 0.0f, // top right
        -0.20f - offset, 0.5f, 0.0f, // top left
	};

    static const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    Shader shaders = Shader("../shaders/vertex.vert", "../shaders/fragment.frag");
    shaders.load_shaders();
    shaders.use();

    Vbo vertices = Vbo(1, GL_ARRAY_BUFFER, (void*)g_vertex_matrix, sizeof(g_vertex_matrix), GL_STATIC_DRAW);
    Vbo elements = Vbo(1, GL_ELEMENT_ARRAY_BUFFER, (void*)indices, 6 * sizeof(unsigned int), GL_STATIC_DRAW);

    glm::vec2 adv = glm::vec2(0, 0);

    shaders.set_vec2("v_Pos", adv);

    float vel = 0.001f;

    do {
        glClear(GL_COLOR_BUFFER_BIT);
        shaders.set_vec2("v_Pos", adv);

        if (glfwGetKey(window.get_handle(), GLFW_KEY_W)) {
            adv.y += vel;
        } else if (glfwGetKey(window.get_handle(), GLFW_KEY_S)) {
            adv.y -= vel;
        } else if (glfwGetKey(window.get_handle(), GLFW_KEY_A)) {
            adv.x -= vel;
        } else if (glfwGetKey(window.get_handle(), GLFW_KEY_D)) {
            adv.x += vel;
        }

        vertices.bind();
        elements.bind();
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glDisableVertexAttribArray(0);
        vertices.unbind();
        elements.unbind();

        window.swap_buffers();
        glfwPollEvents();
    } while (glfwGetKey(window.get_handle(), GLFW_KEY_Q) != GLFW_PRESS &&
        !glfwWindowShouldClose(window.get_handle()));

    return 0;
}
