#include <GL/glew.h>
#include <vao.hpp>
#include <vector>

Vao::Vao(size_t size)
{
    size_ = size;
    glGenVertexArrays(size_, &handle_);
    glBindVertexArray(handle_);
}

Vao::~Vao()
{
    glDeleteVertexArrays(size_, &handle_);
}

void Vao::bind()
{
    glBindVertexArray(this->handle());
}

void Vao::add_vbo(Vbo *vbo)
{
    this->bind();
}

GLuint& Vao::handle()
{
    return handle_;
}

std::vector<Vbo*>& Vao::vbos()
{
    return vbos_;
}
