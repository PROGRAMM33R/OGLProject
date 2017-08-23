#pragma once

#include "Std.hpp"
#include "Camera.hpp"
#include "Config.hpp"

class Controls {

private:
	float initialFoV;
	float speed, mouseSpeed;
	Camera *camera;

public:
	Controls() 
	: 
	  initialFoV(config::FOV),
	  speed(config::SPEED), 
	  mouseSpeed(config::MOUSE_SPEED),
	  camera(new Camera())
	{}
	~Controls();
	void computeMatricesFromInputs(GLFWwindow* window);
	glm::mat4 getMVP() const;

};