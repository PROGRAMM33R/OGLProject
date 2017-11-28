#pragma once

#include "Std.hpp"

class Camera {

private:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 position;
	float horizontalAngle;
	float verticalAngle;
	float initialFoV;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 direction;
	Config *cfg;

public:
	Camera(Config *cfg)
	: 
		horizontalAngle(3.14f),
		verticalAngle(-0.4f),
		cfg(cfg)
	{
		this->position = this->cfg->INIT_CAMERA_POSITION;
		this->initialFoV = this->cfg->FOV;
	}
	~Camera() {}
	void calculateCamera(GLFWwindow* window, float mouseSpeed);
	void calculateMVP(float initialFoV);
	void setPosition(float position, string side);
	glm::mat4 getMVP_(void) const;
	glm::mat4 getProjectionMatrix_(void) const;
	glm::mat4 getViewMatrix_(void) const;
	glm::vec3 getPosition_(void) const;

};