#pragma once

#include <functional>
#include <glm/fwd.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>

namespace sgl {

class Shader {
private:
    std::string vertex_path_;
    std::string fragment_path_;
    GLuint shader_id_;
    bool default_ = false;

public:
    Shader(bool load = false);
    Shader(std::string vert, std::string frag, bool load = false);
    ~Shader();
    
    void use_default_shaders();
    void load_shaders();
    Shader& use();

    Shader& set_vec1(std::string name, glm::vec1& val);
    Shader& set_vec1(std::string name, float x);

    Shader& set_vec2(std::string name, glm::vec2& val);
    Shader& set_vec2(std::string name, float x, float y);

    Shader& set_vec3(std::string name, glm::vec3& val);
    Shader& set_vec3(std::string name, float x, float y, float z);

    Shader& set_vec4(std::string name, glm::vec4& val);
    Shader& set_vec4(std::string name, float x, float y, float z, float w);

    Shader& set_mat3(std::string name, glm::mat3& val);
    Shader& set_mat4(std::string name, glm::mat4& val);

    GLuint& id();
};

}
