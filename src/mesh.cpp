#include "vbo.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <logger.hpp>
#include <mesh.hpp>
#include <utility>
#include <iostream>
#include <vector>

namespace sgl {

Mesh::Mesh(Vao* vao, Shader* shader, Tint tint = Tint())
{
    this->set_shader(shader);
    this->set_vao(vao);

    this->set_tint(tint);
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
        log_warn("Provided NULL as shader. Using default shader.");
        shader_ = new Shader(true);
    }

    shader_->use();

    return *this;
}

Mesh& Mesh::set_tint(Tint tint)
{
    tint_ = tint;
    auto values = tint.values();

    float colors[vertices_ * 3];
    
    for (int i = 0; i < (vertices_ * 3); i += 3)
    {
        colors[i + 0] = std::get<0>(values);
        colors[i + 1] = std::get<1>(values);
        colors[i + 2] = std::get<2>(values);
    }

    ArrayBuffer* colorBuff = new ArrayBuffer(
        (void*)colors,
        sizeof(colors),
        GL_STATIC_DRAW
    );

    colorBuff->set_index(1)
        .set_size(3)
        .set_type(GL_FLOAT)
        .set_normalized(GL_FALSE)
        .set_stride(0);

    vao_->add_array_buffer(colorBuff);

    return *this; 
}

Mesh& Mesh::set_image(TextureBuffer* texBuff)
{
    // this->vao_->add_texture_buffer(texBuff);
    texBuff_ = texBuff;
    
    if (!texBuff_)
    {
        log_error("Provided NULL as TextureBuffer.");
    }

    texBuff->set_vertices({
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,
        0.f, 1.f
    });

    ArrayBuffer* texVbo = new ArrayBuffer(
        (void*)texBuff_->vertices().data(),
        texBuff_->vertices().size() * sizeof(float),
        GL_STATIC_DRAW
    );

    texVbo->set_index(2) // Texture Buffer will always have vertex attrib address 2
        .set_size(2)
        .set_type(GL_FLOAT)
        .set_normalized(false)
        .set_stride(0);

    vao_->add_array_buffer(texVbo);

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

    vao_->bind();

    for (auto arrbuf : vao_->array_buffers())
    {
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
    shader_->set_mat4("mvp_matrix_p", transformation_matrix_);
    shader_->set_vec1("textureSampler", 0);

    glActiveTexture(GL_TEXTURE0);
    this->texBuff_->bind();

    if (vao_->elements())
    {
        glDrawElements(draw_mode_, this->vertices(), GL_UNSIGNED_INT, nullptr);
    } else
    {
        glDrawArrays(draw_mode_, 0, this->vertices());
    }
    vao_->unbind();
}

void Mesh::rotate_degrees(float degree)
{
    this->rotate_degrees(glm::radians(degree));
}

void Mesh::rotate_radians(float radians)
{
    transformation_matrix_ = glm::rotate(
        transformation_matrix_,
        radians,
        glm::vec3(0, 0, 1)
    );
}

void Mesh::scale(glm::vec3 scale_vector)
{
    transformation_matrix_ = glm::scale(transformation_matrix_, scale_vector);
}

void Mesh::translate(glm::vec3 translation_vector)
{
    transformation_matrix_ = glm::translate(transformation_matrix_, translation_vector);
}

}
