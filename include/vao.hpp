#pragma once

#include <cstddef>
#include <vbo.hpp>
#include <GL/gl.h>
#include <vector>

class Vao {
private:
    bool bound_;
    GLuint handle_;
    std::vector<Vbo*> vbos_;
    size_t size_;

public:
    Vao(size_t size);
    ~Vao();
    void add_vbo(Vbo* vbo);
    void bind();
    GLuint& handle();
    std::vector<Vbo*>& vbos();

    static void unbind()
    {
        glBindVertexArray(0);
    }
};
