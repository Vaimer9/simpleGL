#pragma once

#include <cstddef>
#include <map>
#include <utility>
#include <vector>
#include "vbo.hpp"

namespace sgl {

class Vao {
private:
    GLuint handle_;
    std::vector<ArrayBuffer*> array_buffers_;
    size_t size_;
    Vbo* element_buffer_ = nullptr; 

public:
    Vao(size_t size);
    ~Vao();
    void add_array_buffer(ArrayBuffer* vbo);
    void add_array_buffer(std::vector<ArrayBuffer*> vbos);
    void set_element_buffer(Vbo* vbo);
    void bind();

    GLuint& handle();
    bool elements();
    std::vector<ArrayBuffer*>& array_buffers();
    static void unbind()
    {
        glBindVertexArray(0);
    }
};

}
