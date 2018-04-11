#pragma once

#include "Std.hpp"
#include "Camera.hpp"
#include <array>

class Controls {

private:
	float initialFoV;
	float speed, mouseSpeed;
	Camera *camera;
	Config *cfg;
	std::clock_t start;
	bool spacePressed, spaceReleased, startStopwatch;
	bool FPressed, FReleased;
	bool fullscreen;
	const GLFWvidmode * mode;
	
public:
	double escapeDuration;
	int activatedFloor;
	bool updateViewPort;
	std::array< int, 2 > _wndPos{ 0, 0 };
	std::array< int, 2 > _wndSize{ 0, 0 };
	GLFWmonitor * _monitor = nullptr;
	std::array< int, 2 > _vpSize{ 0, 0 };

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
			FPressed = false;
			FReleased = false;
			fullscreen = false;
			updateViewPort = false;
			_monitor = glfwGetPrimaryMonitor();
	}
	~Controls();
	void computeMatricesFromInputs(GLFWwindow* window);
	glm::mat4 getMVP() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getCameraPosition() const;

};