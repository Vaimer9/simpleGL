#pragma once

#include <functional>
#include <glm/fwd.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>

class Shader {
private:
    std::string vertex_;
    std::string fragment_;
    GLuint shader_id_;

public:
    Shader(std::string vert, std::string frag, bool load = false);
    ~Shader();
    
    void load_shaders();
    Shader& use();

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
