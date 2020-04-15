#include "Camera.h"

//Initialize camera and move it baxkwards a bit
Camera::Camera() {
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	updateView();

}

//Update the camera position and direction
void Camera::updateView() {
	updateDirection();
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::updateDirection() {
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);
}

//Handle the keyboard inputs to move the camera and switch view mode
void Camera::handleCameraInput(int key) {

    if (key == 119) //w
        cameraPos += speed * cameraFront;

    if (key == 115) //s
        cameraPos -= speed * cameraFront;

    if (key == 97)//a
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;

    if (key == 100)//d
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;

    if (key == 105) //i
        pitch += speed * 20;

    if (key == 107) //k
        pitch -= speed * 20;

    if (key == 106)//j
        yaw -= speed * 20;

    if (key == 108)//l
        yaw += speed * 20;

    if (key == 99) {//c
        isViewMode = !isViewMode;
        if (isViewMode) {
            //Save last pos data
            lastPitch = pitch;
            lastYaw = yaw;
            lastCameraPos = cameraPos;

            cameraPos = glm::vec3(-25.0f, 10.0f, 3.0f);
            pitch = -15.0f;
            yaw = 0.0f;
        }
        else {
            //set position back to normal
            pitch = lastPitch;
            yaw = lastYaw;
            cameraPos = lastCameraPos;
        }
    }

    //Stop from flying or falling if not in view mode
    if (!isViewMode) {
        cameraPos.y = 0;
    }
}