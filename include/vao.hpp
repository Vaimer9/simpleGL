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
    std::map<int, ArrayBuffer*> array_buffers_;
    size_t size_;
    bool elements_; 
    Shader* shader_;

public:
    Vao(size_t size);
    ~Vao();
    void add_array_buffer(int attribute_index, Vbo* vbo);
    void add_array_buffer(std::vector<std::pair<int, Vbo*>> vbos);
    void add_element_buffer(Vbo* vbo);
    void bind();

    GLuint& handle();
    bool& elements();
    std::map<int, ArrayBuffer*>& array_buffers();
    static void unbind()
    {
        glBindVertexArray(0);
    }
};
