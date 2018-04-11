
#include "Std.hpp"
#include "Controls.hpp"

Controls::~Controls() {
	delete this->camera;
}

void Controls::computeMatricesFromInputs(GLFWwindow* window) {

	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	spacePressed = false;
	spaceReleased = false;
	FPressed = false;
	FReleased = false;
	updateViewPort = false;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		spacePressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		spaceReleased = true;
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		FPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
		FReleased = true;
	}

	if (spacePressed && spaceReleased) {
		if (this->cfg->PATH_FINDING_ENABLED == 1) {
			this->cfg->PATH_FINDING_ENABLED = 0;
			escapeDuration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			startStopwatch = false;
		}
		else {
			this->cfg->PATH_FINDING_ENABLED = 1;
			start = std::clock();
			escapeDuration = 0.0;
			startStopwatch = true;
		}
		spacePressed = false;
		spaceReleased = false;
	}

	if (FPressed && FReleased) {
		fullscreen = !fullscreen;
		mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if (fullscreen) {
			
			//glfwSetWindowSize(window, mode->width, mode->height);
			//glfwSetWindowPos(window, 0, 0);
			
			// backup windwo position and window size
			glfwGetWindowPos(window, &_wndPos[0], &_wndPos[1]);
			glfwGetWindowSize(window, &_wndSize[0], &_wndSize[1]);
			glfwSetWindowMonitor(window, _monitor, 0, 0, mode->width, mode->height, 0);

		}
		else {
			//glfwSetWindowSize(window, cfg->WINDOW_WIDTH, cfg->WINDOW_HEIGHT);
			//glfwSetWindowPos(window, mode->width / 4, mode->height / 4);
			glfwSetWindowMonitor(window, nullptr, _wndPos[0], _wndPos[1], _wndSize[0], _wndSize[1], 0);
		}
		updateViewPort = true;
		FPressed = false;
		FReleased = false;
	}

	if (startStopwatch) {
		escapeDuration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	}

	camera->calculateCamera(window, mouseSpeed);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		this->activatedFloor = 99;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		this->activatedFloor = 90;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		this->activatedFloor = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		this->activatedFloor = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		this->activatedFloor = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		this->activatedFloor = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		this->activatedFloor = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		this->activatedFloor = 5;
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
		this->activatedFloor = 6;
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
		this->activatedFloor = 7;
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
		this->activatedFloor = 8;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS 
		|| glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->setPosition(deltaTime * speed, "up");
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->setPosition(deltaTime * speed, "down");
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->setPosition(deltaTime * speed, "right");
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->setPosition(deltaTime * speed, "left");
	}

	camera->calculateMVP(initialFoV);

	lastTime = currentTime;
}

glm::mat4 Controls::getMVP() const {
	return camera->getMVP_();
}

glm::mat4 Controls::getViewMatrix() const {
	return camera->getViewMatrix_();
}
glm::mat4 Controls::getProjectionMatrix() const {
	return camera->getProjectionMatrix_();
}

glm::vec3 Controls::getCameraPosition() const {
	return camera->getPosition_();
}