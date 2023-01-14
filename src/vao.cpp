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
    for (auto arrbuf : array_buffers_)
    {
        if (arrbuf)
        {
            delete arrbuf;
        }
    }

    glDeleteVertexArrays(size_, &handle_);
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
    this->unbind();
}

void Vao::add_array_buffer(std::vector<ArrayBuffer*> vbos)
{
    for (auto vbo : vbos)
    {
        this->add_array_buffer(vbo);
    }
}

void Vao::set_element_buffer(Vbo *vbo)
{
    element_buffer_ = vbo;
    this->bind();
    vbo->bind();
    this->unbind();

}

bool Vao::elements()
{
    return (element_buffer_ != nullptr);
}

GLuint& Vao::handle()
{
    return handle_;
}

std::vector<ArrayBuffer*>& Vao::array_buffers()
{
    return array_buffers_;
}
