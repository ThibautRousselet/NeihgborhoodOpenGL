#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"

class Camera
{
public :
	glm::vec3 cameraPos;
	glm::vec3 up;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	glm::mat4 view;
	glm::vec3 direction;

	float yaw = -90.0f;
	float pitch = 0.0f;
	float speed = 0.2f;

	bool isViewMode;
	float lastYaw;
	float lastPitch;
	glm::vec3 lastCameraPos;


	Camera();
	void updateView();
	void updateDirection();
	void handleCameraInput(int key);
};

