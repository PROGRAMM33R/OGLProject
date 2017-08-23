
#include "Std.hpp"
#include "Controls.hpp"

Controls::~Controls() {
	delete this->camera;
}

void Controls::computeMatricesFromInputs(GLFWwindow* window) {

	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	camera->calculateCamera(window, mouseSpeed);
	
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