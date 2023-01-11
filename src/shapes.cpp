#include <shapes.hpp>

Rectangle::Rectangle(float x, float y, float wx, float hx)
{
    float h = hx / 2;
    float w = wx / 2;

    const float vertices[] = {
        x - w, y - h, 0,
        x + w, y - h, 0,
        x + w, y + h, 0,
        x - w, y + h, 0
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
    vao->bind();
    vao->add_array_buffer(vertBuff);
    vao->set_element_buffer(elemBuff);

    this->set_vertices(6);
    this->set_vao(vao);
}
