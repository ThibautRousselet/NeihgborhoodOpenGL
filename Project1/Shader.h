#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"

using namespace std;

#include <glm/gtc/matrix_transform.hpp>
class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader();
    Shader(const char* vertexshader_name, const char* fragshader_name);
    // use/activate the shader
    void useProgram();

    // utility uniform functions
    void setVec4(const std::string& name, glm::vec4 value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;
    void setMat3(const std::string& name, glm::mat3 value) const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};

