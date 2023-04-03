#pragma once

#include "shader.hpp"
#include "color.hpp"
#include "vao.hpp"
#include <cstddef>
#include <optional>

namespace sgl {

class Mesh
{
    Vao* vao_ = nullptr;
    Shader* shader_ = nullptr;
    GLenum draw_mode_ = GL_TRIANGLES;
    int vertices_;
    Tint tint_;
public:
    Mesh() {}
    Mesh(Vao* vao, Shader* shader, Tint tint);
    ~Mesh();

    virtual void render();
    int& vertices();

protected:
    Mesh& set_tint(Tint tint);
    Mesh& set_vao(Vao* vao);
    Mesh& set_draw_mode(GLenum mode);
    Mesh& set_shader(Shader* shader);
    Mesh& set_vertices(int vertices);
};

}

