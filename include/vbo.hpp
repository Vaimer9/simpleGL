#pragma once
#include <GL/glew.h>
#include <shader.hpp>

class Vbo {
private:
    void* data_;
    GLuint handle_;
    GLenum target_;
    size_t size_;

public:
    Vbo(size_t buf_size);
    Vbo(size_t buf_size, GLenum target);
    Vbo(size_t buf_size, GLenum target, void* data, size_t data_size, GLenum usage);
    ~Vbo();
    
    void gen_buffers(size_t size);
    void bind();
    void unbind();
    void set_data(GLenum, void* data, size_t data_size, GLenum usage);
    static void unbind(GLenum target) {
        glBindBuffer(target, 0);
    }

    void*& data();
};
