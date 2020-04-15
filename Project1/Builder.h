#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

#include "Cube.h"
#include "Shader.h"
#include "Plane.h"
#include "ModelLoader.h"

class Builder
{
public :
	void buildBuilding(std::vector<Cube> &cubes, std::vector<ModelLoader>& models, Shader shader);
	void buildTrees(std::vector<ModelLoader>& models, Shader shader);
	void buildFloor(std::vector<Plane>& planes, Shader shader);
	void buildCar(std::vector<ModelLoader>& models, Shader shader);
	void buildTree(std::vector<ModelLoader>& models, Shader shader, float x, float z);


	Texture bark = Texture("Resources/Textures/bark.jpg");
	Texture leaves = Texture("Resources/Textures/leaves.jpg");
	Texture bricks = Texture("Resources/Textures/bricks.jpg");
	Texture grass = Texture("Resources/Textures/grass.jpg");
	Texture asphalt = Texture("Resources/Textures/asphalt.jpg");
	Texture redasphalt = Texture("Resources/Textures/redasphalt.jpg");
	Texture metal = Texture("Resources/Textures/metal.jpg");
};

