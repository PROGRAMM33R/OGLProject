#pragma once

#include "MyVector.hpp"

class Object {

private:

public:
	MyVector *location;
	MyVector *size;
	float angle;

	Object(MyVector *location, MyVector *size, float angle)
		:location(location), size(size), angle(angle)
	{}
	Object() {
		this->location = new MyVector(0, 0, 0);
		this->size = new MyVector(0, 0, 0);
		this->angle = 0;
	}

};