#include "Builder.h"

//Contains functions that builds elements from models, also load all the textures on creation

//Set up floor and roads
void Builder::buildFloor(std::vector<Plane> &planes, Shader shader) {
	
	float length = 50.0f; //size of the world
	//Grass floor
	Plane plane = Plane(shader, grass, glm::vec3(length, length, length), 3.0f);
	plane.rotateX = -90.0f;
	plane.position.y = -1.01f;
	planes.push_back(plane);

	//road 1
	plane = Plane(shader, asphalt, glm::vec3(length, 5.0f, 5.0f), 2.0f);
	plane.rotateX = -90.0f;
	plane.position.y = -0.99f;
	planes.push_back(plane);

	//Road 2 
	plane = Plane(shader, asphalt, glm::vec3(5.0f, length, 5.0f), 2.0f);
	plane.rotateX = -90.0f;
	plane.position.y = -0.98f;
	planes.push_back(plane);

	//Bycicle lane 1 
	plane = Plane(shader, redasphalt, glm::vec3(1.0f, length, 1.0f), 2.0f);
	plane.rotateX = -90.0f;
	plane.position.y = -1.0f;
	plane.position.x = 4.0f;
	planes.push_back(plane);

	//Bycicle lane 2
	plane = Plane(shader, redasphalt, glm::vec3(1.0f, length, 1.0f), 3.0f);
	plane.rotateX = -90.0f;
	plane.position.y = -1.0f;
	plane.position.x = -4.0f;
	planes.push_back(plane);
}

//Build building and weathervane on top
void Builder::buildBuilding(std::vector<Cube> &cubes, std::vector<ModelLoader>& models, Shader shader)
{
	//Definition of the building size
	int nbFloor = 12;
	float heightFloor = 1.0f;

	int nbCol = 8;
	float widthCol = 1.0f;
	float totalWidth = nbCol * widthCol;

	float depth = 5.0f;

	float X = 10.0f;
	float Z = 7.0f;


	//load all the windows textures in a vector
	std::vector<Texture> windows;
	for (int i = 0; i < 8; i++) {
		std::string s;
		s.append("Resources/Textures/window");
		s.append(to_string(i + 1));
		s.append(".jpg");
		windows.push_back(Texture(s));
	}
	//Build every cube from the building
	for (int i = 0; i < nbFloor; i++) {
		for (int j = 0; j < nbCol; j++) {

			Cube cube;
			if (j == 0 || j == nbCol - 1 || i == nbFloor-1) {
				cube = Cube(shader, bricks, glm::vec3(depth, heightFloor, widthCol), 1.0f);
			}
			else {
				//Get a random window texture to create a more natural aspect
				cube = Cube(shader, windows [rand() % windows.size()], glm::vec3(depth, heightFloor, widthCol), 1.0f);
			}
			//We pile up the blocks to build the structure
			cube.position.y = i * heightFloor + (heightFloor / 2)-1.0f;
			cube.position.x = X-depth/2.0f;
			cube.position.z = -(totalWidth / 2.0f) + (j + 0.5f) * widthCol+Z;

			cubes.push_back(cube);
		}
	}

	//Add a weathervane on top on the building and make it spin
	ModelLoader vane = ModelLoader("Resources/Models/weathervane.obj", shader, metal);
	vane.position.y = (nbFloor) * heightFloor + (heightFloor / 2)-1.5f;
	vane.position.x = X-4.5f;
	vane.position.z = -(totalWidth / 2.0f) + (1 + 0.5f) * widthCol + Z;
	vane.sizeRatio = glm::vec3(0.2f, 0.2f, 0.2f);
	vane.animRotateY = 0.4f;
	models.push_back(vane);
}

//Build trees at defined locations
void Builder::buildTrees(std::vector<ModelLoader>& models, Shader shader) {

	//Front right
	buildTree(models, shader, 10.0f, -15.0f);

	//front left
	buildTree(models, shader, -10.0f, -20.0f);
	buildTree(models, shader, -13.0f, -24.0f);
	buildTree(models, shader, -6.0f, -8.0f);
	buildTree(models, shader, -10.0f, -10.0f);

	//back left
	buildTree(models, shader, -12.0f, 20.0f);
	buildTree(models, shader, -16.0f, 10.0f);
	buildTree(models, shader, -8.0f, 12.0f);
	buildTree(models, shader, -8.0f, 18.0f);
}

void Builder::buildTree(std::vector<ModelLoader>& models, Shader shader, float x, float z) {
	ModelLoader base =  ModelLoader("Resources/Models/cylinder32.obj", shader, Texture("Resources/Textures/bark.jpg"));
	base.position = glm::vec3(x, -1.0f, z);
	base.sizeRatio = glm::vec3(0.2f, 2.0f, 0.2f);
	models.push_back(base);

	ModelLoader leaveSphere = ModelLoader("Resources/Models/sphere.obj", shader, Texture("Resources/Textures/leaves.jpg"));
	leaveSphere.position = glm::vec3(x, 2.0f, z);
	leaveSphere.sizeRatio = glm::vec3(1.2f, 1.5f, 1.2f);
	leaveSphere.nbRepetition = 2.0f;
	models.push_back(leaveSphere);
}

//Load the car model and animate it to move along the road
void Builder::buildCar(std::vector<ModelLoader>& models, Shader shader) {

	ModelLoader car = ModelLoader("Resources/Models/car.obj", shader, Texture("Resources/Textures/metal.jpg"));
	car.rotateX = -90.0f;
	car.animPosition = glm::vec3(0.0f, -0.0f, 0.02f);
	car.animMaxPosition.z = 15.0f;
	car.animDefaultPosition.z = -15.0f;

	car.position.y = -0.8f;
	car.animDefaultPosition.y = -0.8f;

	car.position.x = -1.3f;
	car.animDefaultPosition.x = -1.3f;

	car.sizeRatio = glm::vec3(0.01f, 0.01f, 0.01f);

	models.push_back(car);
}