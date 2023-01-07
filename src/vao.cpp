#include <GL/glew.h>
#include <algorithm>
#include <vao.hpp>
#include <vector>

Vao::Vao(size_t size)
{
    size_ = size;
    glGenVertexArrays(size_, &handle_);
}

Vao::~Vao()
{
    glDeleteVertexArrays(size_, &handle_);
}

void Vao::bind()
{
    glBindVertexArray(this->handle());
}

void Vao::add_array_buffer(int attribute_index, Vbo* vbo)
{
    this->bind();
    vbo->bind();
    array_buffers_[attribute_index] = (ArrayBuffer*)vbo;
}

void Vao::add_array_buffer(std::vector<std::pair<int, Vbo*>> vbos)
{
    for (auto vbo : vbos)
    {
        this->add_array_buffer(vbo.first, vbo.second);
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

std::map<int, ArrayBuffer*>& Vao::array_buffers()
{
    return array_buffers_;
}
