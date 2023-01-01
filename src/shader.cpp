#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <shader.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string vert, std::string frag):
    vertex_(vert), fragment_(frag) {};

Shader::~Shader()
{
    glDeleteProgram(this->id());
}

GLuint& Shader::id()
{
    return shader_id_;
}

void Shader::load_shaders()
{
    // Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	} else {
        std::cout << "Couldn't open " << vertex_ << "Are you in the right directory?" << std::endl;
		getchar();
		return;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
    std::cout << "Compiling shader" << vertex_ << std::endl;
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        std::cout << &VertexShaderErrorMessage[0] << std::endl;
	}

	// Compile Fragment Shader
    std::cout << "Compiling shader" << fragment_ << std::endl;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        std::cout << &FragmentShaderErrorMessage[0] << std::endl;
	}

	// Link the program
    std::cout << "Linking Program" << std::endl;
	shader_id_ = glCreateProgram();
	glAttachShader(shader_id_, VertexShaderID);
	glAttachShader(shader_id_, FragmentShaderID);
	glLinkProgram(shader_id_);

	// Check the program
	glGetProgramiv(shader_id_, GL_LINK_STATUS, &Result);
	glGetProgramiv(shader_id_, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(shader_id_, InfoLogLength, NULL, &ProgramErrorMessage[0]);
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

Shader& Shader::set_vec3(std::string name, glm::vec3& val)
{
    glUniform3f(glGetUniformLocation(this->id(), name.c_str()), val.x, val.y, val.z);
    return *this;
}

Shader& Shader::set_vec4(std::string name, glm::vec4& val)
{
    glUniform4f(glGetUniformLocation(this->id(), name.c_str()), val.x, val.y, val.z, val.w);
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
