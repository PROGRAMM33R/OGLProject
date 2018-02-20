#pragma once

#include "Std.hpp"
#include "Camera.hpp"

class Controls {

private:
	float initialFoV;
	float speed, mouseSpeed;
	Camera *camera;
	Config *cfg;
	std::clock_t start;
	bool spacePressed, spaceReleased, startStopwatch;
	
public:
	double escapeDuration;
	int activatedFloor;

	Controls(Config *cfg)
	:
		camera(new Camera(cfg)),
		cfg(cfg)
	{
			this->initialFoV = this->cfg->FOV;
			this->speed = this->cfg->PLAYER_SPEED;
			this->mouseSpeed = this->cfg->MOUSE_SPEED;
			this->activatedFloor = 99;
			spacePressed = false;
			spaceReleased = false;
			startStopwatch = false;
	}
	~Controls();
	void computeMatricesFromInputs(GLFWwindow* window);
	glm::mat4 getMVP() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getCameraPosition() const;

};