#include "logger.hpp"
#include <mesh.hpp>
#include <utility>
#include <iostream>

namespace sgl {

Mesh::Mesh(Vao* vao)
{
    vao_ = vao;
}

Mesh::Mesh(Vao* vao, Shader* shader)
{
    vao_ = vao;
    shader_ = shader;
    if (!shader_)
    {
        log_error("Provided nullptr as shader. Using default shader.");
        shader_ = new Shader(true);
    }
}

Mesh::~Mesh()
{
    if (vao_) delete vao_;
    if (shader_) delete shader_;
}

Mesh& Mesh::set_vao(Vao* vao)
{
    vao_ = vao;
    return *this;
}

Mesh& Mesh::set_shader(Shader* shader)
{
    shader_ = shader;
    if (!shader_)
    {
        log_error("Provided nullptr as shader. Using default shader.");
        shader_ = new Shader(true);
    }
    return *this;
}

Mesh& Mesh::set_vertices(int vertices)
{
    vertices_ = vertices; 
    return *this;
}

Mesh& Mesh::set_draw_mode(GLenum mode)
{
    draw_mode_ = mode;
    return *this;
}

int& Mesh::vertices()
{
    return vertices_;
}

void Mesh::render()
{
    if (!vao_)
    {
        log_error("Missing VAO in mesh during render call");
        return;
    }

    shader_->use();

    for (auto arrbuf : vao_->array_buffers())
    {
        vao_->bind();
        arrbuf->bind();
        glEnableVertexAttribArray(arrbuf->index());
        glVertexAttribPointer(
            arrbuf->index(),
            arrbuf->size(),
            arrbuf->type(),
            arrbuf->normalized(),
            arrbuf->stride(),
            (void*)0
        );
        arrbuf->unbind();
    }

    if (vao_->elements())
    {
        glDrawElements(draw_mode_, this->vertices(), GL_UNSIGNED_INT, nullptr);
    } else
    {
        glDrawArrays(draw_mode_, 0, this->vertices());
    }
    vao_->unbind();
}

}
