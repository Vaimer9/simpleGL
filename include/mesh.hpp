#pragma once

#include "shader.hpp"
#include "vao.hpp"

class Mesh
{
    Vao* vao_ = NULL;
    Shader* shader_ = NULL;
    int vertices_;
public:

    Mesh() {}
    Mesh(Vao* vao);
    Mesh(Vao* vao, Shader* shader);
    ~Mesh();

    Mesh& set_vao(Vao* vao);
    Mesh& set_shader(Shader* shader);
    Mesh& set_vertices(int vertices);

    virtual void render();
    int& vertices();
};
