#include "logger.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <shader.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sgl {

std::string default_vertex =
"#version 330 core\n"
"layout(location = 0) in vec3 v_Org;\n"
"void main() {\n"
"   gl_Position = vec4(v_Org, 1);\n"
"}";

std::string default_fragment =
"#version 330 core\n"
"out vec4 color;\n"
"void main() {\n"
"   color = vec4(1, 1, 1, 1);\n"
"}";

Shader::Shader(std::string vert, std::string frag, bool load):
    vertex_path_(vert), fragment_path_(frag)
{
    if (load)
    {
        this->load_shaders();
    }
};

Shader::Shader(bool load)
{
    default_ = true;
    if (load)
    {
        this->load_shaders();
    }
}

Shader::~Shader()
{
    glDeleteProgram(this->id());
}

GLuint& Shader::id()
{
    return shader_id_;
}

void Shader::use_default_shaders()
{
    default_ = true;
}

void Shader::load_shaders()
{
    // Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::string FragmentShaderCode;
    
    if (default_)
    {
        VertexShaderCode = default_vertex;
        FragmentShaderCode = default_fragment;
    }
    else
    {
        std::ifstream VertexShaderStream(vertex_path_, std::ios::in);
        if (VertexShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        } else {
            log_error("Could not open " + vertex_path_);
            getchar();
            return;
        }

        std::ifstream FragmentShaderStream(fragment_path_, std::ios::in);
        if (FragmentShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }
    }

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        std::cout << &VertexShaderErrorMessage[0] << std::endl;
	}

	// Compile Fragment Shader
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        std::cout << &FragmentShaderErrorMessage[0] << std::endl;
	}

	// Link the program
	shader_id_ = glCreateProgram();
	glAttachShader(shader_id_, VertexShaderID);
	glAttachShader(shader_id_, FragmentShaderID);
	glLinkProgram(shader_id_);

	// Check the program
	glGetProgramiv(shader_id_, GL_LINK_STATUS, &Result);
	glGetProgramiv(shader_id_, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(shader_id_, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        std::cout << &ProgramErrorMessage << std::endl;
	}
	
	glDetachShader(shader_id_, VertexShaderID);
	glDetachShader(shader_id_, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
}

Shader& Shader::use()
{
    glUseProgram(shader_id_);
    return *this;
}

Shader& Shader::set_vec2(std::string name, glm::vec2& val)
{
    glUniform2f(glGetUniformLocation(this->id(), name.c_str()), val.x, val.y);
    return *this;
}

Shader& Shader::set_vec2(std::string name, float x, float y)
{
    glUniform2f(glGetUniformLocation(this->id(), name.c_str()), x, y);
    return *this;
}

Shader& Shader::set_vec3(std::string name, glm::vec3& val)
{
    glUniform3f(glGetUniformLocation(this->id(), name.c_str()), val.x, val.y, val.z);
    return *this;
}

Shader& Shader::set_vec3(std::string name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(this->id(), name.c_str()), x, y, z);
    return *this;
}

Shader& Shader::set_vec4(std::string name, glm::vec4& val)
{
    glUniform4f(glGetUniformLocation(this->id(), name.c_str()), val.x, val.y, val.z, val.w);
    return *this;
}

Shader& Shader::set_vec4(std::string name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(this->id(), name.c_str()), x, y, z, w);
    return *this;
}

Shader& Shader::set_mat3(std::string name, glm::mat3& val)
{
    glUniformMatrix3fv(glGetUniformLocation(this->id(), name.c_str()), 1, false, glm::value_ptr(val));
    return *this;
}

Shader& Shader::set_mat4(std::string name, glm::mat4& val)
{
    glUniformMatrix4fv(glGetUniformLocation(this->id(), name.c_str()), 1, false, glm::value_ptr(val));
    return *this;
}

}
