#pragma once

#include "shader.hpp"
#include "vao.hpp"

class Mesh {
private:
    Vao* vao_;
    Shader* shader_;
    int vertices_;
public:

    Mesh() {}
    Mesh(Vao* vao);
    Mesh(Vao* vao, Shader* shader);

    Mesh* set_vao(Vao* vao);
    Mesh* set_shader(Shader* shader);
    Mesh* set_vertices(int vertices);

    virtual void render();
    int& vertices();
};
