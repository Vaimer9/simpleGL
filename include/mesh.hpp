#pragma once

#include "shader.hpp"
#include "color.hpp"
#include "texture.hpp"
#include "vao.hpp"
#include <cstddef>
#include <optional>
#include <glm/mat3x3.hpp>

namespace sgl {

class Mesh
{
    Vao* vao_ = nullptr;
    Shader* shader_ = nullptr;
    GLenum draw_mode_ = GL_TRIANGLES;
    int vertices_;
    Tint tint_;
    Texture texture_;
    glm::mat4 transformation_matrix_ = glm::mat4(1);

public:
    Mesh() {}
    Mesh(Vao* vao, Shader* shader, Tint tint);
    ~Mesh();

    void rotate_degrees(float degree);
    void rotate_radians(float radians);
    void scale(glm::vec3 scale_matrix);
    void translate(glm::vec3 translation_matrix);
    void set_texture(Texture texture);

    virtual void render();
    int& vertices();

protected:
    Mesh& set_tint(Tint tint);
    Mesh& set_vao(Vao* vao);
    Mesh& set_draw_mode(GLenum mode);
    Mesh& set_shader(Shader* shader);
    Mesh& set_vertices(int vertices);
};

} // namespace sgl

