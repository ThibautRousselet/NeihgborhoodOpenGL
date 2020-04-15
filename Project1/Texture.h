#pragma once

#include<string>
#include<vector>
#include <GL\glew.h>

class Texture
{
public :
	unsigned int ID;

	Texture(std::string file); //2d texture
	Texture(std::vector<std::string> faces); //Texture for skybox
	Texture();
};

