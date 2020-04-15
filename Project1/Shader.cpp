#include "Shader.h"

//Shader class that initializes a shader and stores its ID
Shader::Shader(const char* vertexshader_name, const char* fragshader_name) {
	char* vertexshader = glsl::readFile(vertexshader_name);
	GLuint vsh_id = glsl::makeVertexShader(vertexshader);

	char* fragshader = glsl::readFile(fragshader_name);
	GLuint fsh_id = glsl::makeFragmentShader(fragshader);

	ID = glsl::makeShaderProgram(vsh_id, fsh_id);

	//No need to keep the shaders, they are now in the program
	glDeleteShader(vsh_id);
	glDeleteShader(fsh_id);
}

Shader::Shader() {
	ID = 0;
}

void Shader::useProgram()
{
	glUseProgram(ID);
}

//Setters of the uniform values in the shader

void Shader::setVec4(const std::string& name, glm::vec4 value) const
{
	int vectorloc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(vectorloc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	int vectorloc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(vectorloc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	int vectorloc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix3fv(vectorloc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat3(const std::string& name, glm::mat3 value) const
{
	int vectorloc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(vectorloc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}