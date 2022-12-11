#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

#include <utils.hpp>
#include <config.hpp>

int main()
{
    GLFWwindow* window = gl_init();

    GLuint vbo;
    glGenVertexArrays(1, &vbo);
    glBindVertexArray(vbo);

    static const GLfloat g_vertex_matrix[] = { 
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
	};

    static const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    GLuint programID = load_shaders("../shaders/vertex.vert", "../shaders/fragment.frag");

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_matrix), g_vertex_matrix, GL_STATIC_DRAW);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    glUseProgram(programID);

    GLuint v_loc = glGetUniformLocation(programID, "v_Pos");

    glUniform2f(v_loc, 0.f, 0.f);


    float vel = 0.001f;

    float x, y = 0;
    do {
        glClear( GL_COLOR_BUFFER_BIT );
        glUniform2f(v_loc, x, y);
        
        if (glfwGetKey(window, GLFW_KEY_W)) {
            y += vel;
        } else if (glfwGetKey(window, GLFW_KEY_S)) {
            y -= vel;
        } else if (glfwGetKey(window, GLFW_KEY_A)) {
            x -= vel;
        } else if (glfwGetKey(window, GLFW_KEY_D)) {
            x += vel;
        }

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        /* glDrawArrays(GL_TRIANGLES, 0, 6); */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_Q ) != GLFW_PRESS &&
        !glfwWindowShouldClose(window));

    glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vbo);

    glfwTerminate();
    return 0;
}
