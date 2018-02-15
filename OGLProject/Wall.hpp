#pragma once

#include "Object.hpp"
#include "MyVector.hpp"

class Wall : public Object {

private:

public:
	int meshSize;

	Wall(MyVector *location, MyVector *size, float angle, int meshSize = 0){
		this->location = location;
		this->size = size;
		this->angle = angle;
		this->meshSize = meshSize;
	}
	Wall() {
		Object();
		this->meshSize = 0;
	}

};