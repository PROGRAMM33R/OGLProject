#pragma once

#include "Std.hpp"
#include "Object.hpp"

class Actor : public Object {

public:
	GLfloat direction;
	GLfloat velocity;

	Actor();
	Actor(glm::vec3 pos, glm::vec2 size, GLfloat direction, GLfloat velocity = 0.0);
	void move();

};