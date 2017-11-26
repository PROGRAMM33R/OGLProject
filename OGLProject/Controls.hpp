#pragma once

#include "Std.hpp"
#include "Camera.hpp"

class Controls {

private:
	float initialFoV;
	float speed, mouseSpeed;
	Camera *camera;

public:
	Controls() 
	: 
		camera(new Camera()),
		initialFoV(Config::FOV),
		speed(Config::PLAYER_SPEED),
		mouseSpeed(Config::MOUSE_SPEED)
	{}
	~Controls();
	void computeMatricesFromInputs(GLFWwindow* window);
	glm::mat4 getMVP() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getCameraPosition() const;

};