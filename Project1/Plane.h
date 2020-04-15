#pragma once
#include "Model.h"

class Plane : public Model
{
public :
	Plane(Shader shad, Texture text);
	Plane(Shader shad, Texture text, glm::vec3 ratio, float nbRep);
	Plane();
	void InitBuffer() override;
};

