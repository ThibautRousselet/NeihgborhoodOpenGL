#pragma once
#include "Model.h"

class Cube : public Model
{
public :
	Cube(Shader shad, Texture text);
	Cube(Shader shad, Texture text, glm::vec3 ratio, float nbRep);
	Cube();
	void InitBuffer() override;
};

