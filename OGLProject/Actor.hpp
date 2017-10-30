#pragma once

#include "Std.hpp"
#include "Object.hpp"

class Actor : public Object {

public:
	Actor();
	Actor(glm::vec3 pos, glm::vec2 size, glm::vec2 direction, glm::vec3 color = glm::vec3(1.0f), float velocity = 0.0);

	void Draw(Model &renderer);

private:
	glm::vec2 Direction;
	float Velocity;

};