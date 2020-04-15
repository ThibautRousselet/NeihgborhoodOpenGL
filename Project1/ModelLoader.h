#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "objloader.h"

class ModelLoader : public Model
{
public :
	ModelLoader(const char* path, Shader shad, Texture text);
	//ModelLoader(Shader shad, Texture text);
	ModelLoader();
	void InitBuffer() override;

	vector<glm::vec3> normals;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	const char* path;
};

