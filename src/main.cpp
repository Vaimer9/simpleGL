#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <window.hpp>
#include <shader.hpp>
#include <mesh.hpp>
#include <shapes.hpp>
#include <utils.hpp>

const float vel = 0.005f;
float x, y = 0;

int main()
{
    Utilities::glfw_init();
    Window window = Window("Opengl Window", 800, 600, true);
    window.set_exit_key(GLFW_KEY_Q);

    Shader shaders = Shader("../shaders/vertex.vert", "../shaders/fragment.frag", true);

    glm::vec2 adv = glm::vec2(0, 0);
    shaders.set_vec2("v_Pos", x, y);

    Rectangle rectangle = Rectangle(0, 0, 0.5, 0.5);
    rectangle.set_shader(&shaders);


    window.loop([&] {
        // Talk with the shader, even though the attrib data is not explicitly sent
        shaders.set_vec2("v_Pos", x, y);

        if (window.get_key(GLFW_KEY_W)) {
            y += vel;
        } else if (window.get_key(GLFW_KEY_S)) {
            y -= vel;
        } else if (window.get_key(GLFW_KEY_A)) {
            x -= vel;
        } else if (window.get_key(GLFW_KEY_D)) {
            x += vel;
        }

        rectangle.render();
    });

    return 0;
}
