#pragma once

#include "shader.hpp"
#include "vao.hpp"

namespace sgl {

class Mesh
{
    Vao* vao_ = nullptr;
    Shader* shader_ = nullptr;
    GLenum draw_mode_ = GL_TRIANGLES;
    int vertices_;
public:

    Mesh() {}
    Mesh(Vao* vao);
    Mesh(Vao* vao, Shader* shader);
    ~Mesh();

    Mesh& set_vao(Vao* vao);
    Mesh& set_draw_mode(GLenum mode);
    Mesh& set_shader(Shader* shader);
    Mesh& set_vertices(int vertices);

    virtual void render();
    int& vertices();
};

}

