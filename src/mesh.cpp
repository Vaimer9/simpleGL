#include <mesh.hpp>
#include <utility>
#include <iostream>

Mesh::Mesh(Vao* vao)
{
    vao_ = vao;
}

Mesh::Mesh(Vao* vao, Shader* shader)
{
    vao_ = vao;
    shader_ = shader;
}

Mesh* Mesh::set_vao(Vao* vao)
{
    vao_ = vao;
    return this;
}

Mesh* Mesh::set_shader(Shader* shader)
{
    shader_ = shader;
    return this;
}

Mesh* Mesh::set_vertices(int vertices)
{
    vertices_ = vertices; 
    return this;
}

int& Mesh::vertices()
{
    return vertices_;
}

void Mesh::render()
{
    vao_->bind();

    for (auto pair : vao_->array_buffers())
    {
        vao_->bind();
        glEnableVertexAttribArray(pair.first);
        glVertexAttribPointer(
            pair.first,
            pair.second->size(),
            pair.second->type(),
            pair.second->normalized(),
            pair.second->stride(),
            (void*)0
        );
    }

    if (vao_->elements())
    {
        glDrawElements(GL_TRIANGLES, this->vertices(), GL_UNSIGNED_INT, nullptr);
    } else
    {
        glDrawArrays(GL_TRIANGLES, 0, this->vertices());
    }
}
