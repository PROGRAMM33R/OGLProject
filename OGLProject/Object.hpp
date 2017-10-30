#pragma once

#include "Std.hpp"
#include "Model.hpp"

class Object {

public:
	glm::vec3   Position, Color;
	glm::vec2   Size;

	Object()
		: Position(0, 0, 0), Size(1, 1), Color(1.0f) { }
	Object(glm::vec3 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f))
		: Position(pos), Size(size), Color(color) { }
	
	virtual void Draw(Model &renderer);
	
};