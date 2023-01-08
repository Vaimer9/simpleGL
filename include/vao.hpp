#pragma once

#include <cstddef>
#include <map>
#include <utility>
#include <vbo.hpp>
#include <GL/gl.h>
#include <vector>

class Vao {
private:
    bool bound_;
    GLuint handle_;
    std::vector<ArrayBuffer*> array_buffers_;
    size_t size_;
    bool elements_; 
    Shader* shader_;

public:
    Vao(size_t size);
    ~Vao();
    void add_array_buffer(ArrayBuffer* vbo);
    void add_array_buffer(std::vector<ArrayBuffer*> vbos);
    void add_element_buffer(Vbo* vbo);
    void bind();

    GLuint& handle();
    bool& elements();
    std::vector<ArrayBuffer*>& array_buffers();
    static void unbind()
    {
        glBindVertexArray(0);
    }
};
