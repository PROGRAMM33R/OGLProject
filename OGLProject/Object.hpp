#pragma once

#include "Std.hpp"
#include "Model.hpp"

class Object {

public:
	glm::vec3 position;
	glm::vec2 size;

	Object()
		: position(0, 1, 0), size(1, 1) { }
	Object(glm::vec3 pos, glm::vec2 size)
		: position(pos), size(size) { }
	
};