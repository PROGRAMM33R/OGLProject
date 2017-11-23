
#include "Std.hpp"
#include "Camera.hpp"

void Camera::calculateCamera(GLFWwindow* window, float mouseSpeed) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	
	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	up = glm::cross(right, direction);
}

void Camera::calculateMVP(float initialFoV) {
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); 

						   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 50000.0f);

	ViewMatrix = glm::lookAt(
		position,
		position + direction,
		up
	);
}

void Camera::setPosition(float position, string side) {
	if (side == "up") {
		this->position += position * direction;
	}
	else if (side == "down") {
		this->position -= position * direction;
	}
	else if (side == "right") {
		this->position += position * right;
	}
	else if (side == "left") {
		this->position -= position * right;
	}
}

glm::mat4 Camera::getMVP_(void) const {
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	return ProjectionMatrix * ViewMatrix * ModelMatrix;
}

glm::mat4 Camera::getProjectionMatrix_(void) const {
	return this->ProjectionMatrix;
}
glm::mat4 Camera::getViewMatrix_(void) const {
	return this->ViewMatrix;
}
glm::vec3 Camera::getPosition_(void) const {
	return this->position;
}