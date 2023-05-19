#include <glm/ext/scalar_constants.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <shapes.hpp>

namespace sgl {

#define T_PI(__TYPE__) (2 * glm::pi<__TYPE__>())

Rectangle::Rectangle(glm::vec2 center, float wx, float hx, Tint tint)
{
    float h = hx / 2;
    float w = wx / 2;

    const float vertices[] = {
        center.x - w, center.y - h, 0,
        center.x + w, center.y - h, 0,
        center.x + w, center.y + h, 0,
        center.x - w, center.y + h, 0
    };

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    ArrayBuffer* vertBuff = new ArrayBuffer(
        (void*)vertices,
        sizeof(vertices),
        GL_STATIC_DRAW
    );

    vertBuff->set_index(0)
        .set_size(3)
        .set_type(GL_FLOAT)
        .set_normalized(GL_FALSE)
        .set_stride(0);

    Vbo* elemBuff = new Vbo(
        GL_ELEMENT_ARRAY_BUFFER,
        (void*)indices,
        sizeof(indices),
        GL_STATIC_DRAW
    );

    Vao* vao = new Vao(1);
    vao->add_array_buffer(vertBuff);
    vao->set_element_buffer(elemBuff);

    this->set_vertices(6);
    this->set_vao(vao);
    this->set_tint(tint); // Make sure this comes after .set_vao(..) because color buffer needs
                          // a VAO to be added into
    this->set_shader(nullptr);
}

Triangle::Triangle(glm::vec2 first, glm::vec2 second, glm::vec2 third, Tint tint)
{
    const float vertices[] = {
        first.x, first.y, 0,
        second.x, second.y, 0,
        third.x, third.y, 0
    };

    ArrayBuffer* vertBuff = new ArrayBuffer(
        (void*)vertices,
        sizeof(vertices),
        GL_STATIC_DRAW
    );

    vertBuff->set_index(0)
        .set_size(3)
        .set_type(GL_FLOAT)
        .set_normalized(GL_FALSE)
        .set_stride(0);

    Vao* vao = new Vao(1);
    vao->add_array_buffer(vertBuff);

    this->set_vertices(3);
    this->set_vao(vao);
    this->set_tint(tint);
    this->set_shader(nullptr);
}

Circle::Circle(glm::vec2 center, float radius, int precision, Tint tint)
{
    std::vector<float> vertices;
    for (double i = 0; i < T_PI(double); i += T_PI(double) / precision) {
        vertices.push_back(center.x + glm::cos(i) * radius);
        vertices.push_back(center.y + glm::sin(i) * radius);
        vertices.push_back(0.0);
    }

    ArrayBuffer* vertBuff = new ArrayBuffer(
        vertices.data(),
        vertices.size() * sizeof(float),
        GL_STATIC_DRAW
    );

    vertBuff->set_index(0)
        .set_size(3)
        .set_type(GL_FLOAT)
        .set_normalized(GL_FALSE)
        .set_stride(0);

    Vao* vao = new Vao(1);
    vao->add_array_buffer(vertBuff);

    this->set_vertices(vertices.size() / 3);
    this->set_draw_mode(GL_TRIANGLE_FAN);
    this->set_vao(vao);
    this->set_tint(tint);
    this->set_shader(nullptr);
}

}
