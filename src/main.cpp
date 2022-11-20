#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <utils.hpp>
#include <config.hpp>

int main()
{
    GLFWwindow* window = gl_init();

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    const GLfloat g_vertex_matrix[] = {
       0.f, 1.f, 0.f,    // V1.position
       1.f, -1.f, 0.f,   // V2.position
       -1.f, -1.f, 0.f,
    };

    const GLfloat colorData[] = {
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };

    GLuint programID = load_shaders("shaders/vertex.vert", "shaders/fragment.frag");

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_matrix), g_vertex_matrix, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorbuffer), colorData, GL_STATIC_DRAW);

    glm::mat4 projection = glm::perspective(
        glm::radians((float)CAMERA_FOV),
        16.0f / 9.0f, 0.1f, 100.0f
    );

    glm::mat4 view = glm::lookAt(
        glm::vec3(4, 3, -3),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = projection * view * model;

    GLuint matrix_id = glGetUniformLocation(programID, "MVP");
    GLuint color_id = glGetAttribLocation(programID, "CLR");

    // Main Loop
    do {
        /* glClear( GL_COLOR_BUFFER_BIT ); */
        /* glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); */

        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);
        glEnableVertexAttribArray(matrix_id);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(matrix_id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(color_id);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(color_id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glUseProgram(programID);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window));

    glfwTerminate();
    return 0;
}
