#include <vbo.hpp>

Vbo::Vbo(size_t buf_size, GLenum target)
{
    size_ = buf_size;
    target_ = target;
    glGenBuffers(buf_size, &handle_);
}

Vbo::Vbo(size_t buf_size, GLenum target, void* data, size_t data_size, GLenum usage)
{
    data_ = data;
    target_ = target;
    size_ = buf_size;

    glGenBuffers(buf_size, &handle_);
    this->bind();
    glBufferData(target, data_size, data_, usage);
    Vbo::unbind(target_);
}

Vbo::~Vbo()
{
    glDeleteBuffers(this->size_, &this->handle_);
}

void Vbo::gen_buffers(size_t buf_size)
{
    this->bind();
    glGenBuffers(buf_size, &handle_);
    glBindBuffer(target_, 0);
    Vbo::unbind(target_);
}

void Vbo::bind()
{
    glBindBuffer(target_, handle_);
}

void Vbo::unbind()
{
    Vbo::unbind(target_);
}

void Vbo::set_data(GLenum target, void* data, size_t data_size, GLenum usage)
{
    data_ = data;
    this->bind();
    glBufferData(target, data_size, data_, usage);
    Vbo::unbind(target_);
}
