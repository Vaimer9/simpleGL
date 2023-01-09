#include <GL/glew.h>
#include <algorithm>
#include <vao.hpp>
#include <vector>
#include <iostream>

Vao::Vao(size_t size)
{
    size_ = size;
    glGenVertexArrays(size_, &handle_);
}

Vao::~Vao()
{
    // Todo: Delete this stuff
    /* glDeleteVertexArrays(size_, &handle_); */
}

void Vao::bind()
{
    glBindVertexArray(this->handle());
}

void Vao::add_array_buffer(ArrayBuffer* vbo)
{
    this->bind();
    vbo->bind();
    array_buffers_.push_back(vbo);

}

void Vao::add_array_buffer(std::vector<ArrayBuffer*> vbos)
{
    for (auto vbo : vbos)
    {
        this->add_array_buffer(vbo);
    }
}

void Vao::add_element_buffer(Vbo *vbo)
{
    this->bind();
    vbo->bind();
    elements_ = true;
}

bool& Vao::elements()
{
    return elements_;
}

GLuint& Vao::handle()
{
    return handle_;
}

std::vector<ArrayBuffer*>& Vao::array_buffers()
{
    return array_buffers_;
}
