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

    for (auto arrbuf : vao_->array_buffers())
    {
        vao_->bind();
        glEnableVertexAttribArray(arrbuf->index());
        glVertexAttribPointer(
            arrbuf->index(),
            arrbuf->size(),
            arrbuf->type(),
            arrbuf->normalized(),
            arrbuf->stride(),
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
