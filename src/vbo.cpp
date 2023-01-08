#include <vbo.hpp>
#include <iostream>

Vbo::Vbo(GLenum target)
{
    target_ = target;
    glGenBuffers(1, &handle_);
}

Vbo::Vbo(GLenum target, void* data, size_t data_size, GLenum usage)
{
    data_ = data;
    target_ = target;

    glGenBuffers(1, &handle_);
    this->bind();
    glBufferData(target, data_size, data_, usage);
    this->unbind();
}

Vbo::~Vbo()
{
    glDeleteBuffers(1, &this->handle_);
}

GLenum& Vbo::target()
{
    return target_;
}

void Vbo::gen_buffers()
{
    this->bind();
    glGenBuffers(1, &handle_);
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
    target_ = target;

    this->bind();
    glBufferData(target, data_size, data_, usage);
    Vbo::unbind(target_);
}

ArrayBuffer::ArrayBuffer(void* data, size_t data_size, GLenum usage)
{
    data_ = data;
    target_ = GL_ARRAY_BUFFER;

    glGenBuffers(1, &handle_);
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, data_size, data, usage);
}

void ArrayBuffer::unbind()
{
    Vbo::unbind(GL_ARRAY_BUFFER);
}

ArrayBuffer& ArrayBuffer::set_size(size_t size)
{
    size_ = size;
    return *this;
}

ArrayBuffer& ArrayBuffer::set_type(GLenum type)
{
    type_ = type;
    return *this;
}

ArrayBuffer& ArrayBuffer::set_normalized(bool normalized)
{
    normalized_ = normalized;
    return *this;
}

ArrayBuffer& ArrayBuffer::set_stride(size_t stride)
{
    stride_ = stride;
    return *this;
}

size_t& ArrayBuffer::size()
{
    return size_;
}

GLenum& ArrayBuffer::type()
{
    return type_;
}

bool& ArrayBuffer::normalized()
{
    return normalized_;
}

size_t& ArrayBuffer::stride()
{
    return stride_;
}


