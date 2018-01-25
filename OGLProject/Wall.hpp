#pragma once

#include "Std.hpp"
#include "MyVector.hpp"

class Wall {

private:

public:
	MyVector *location;
	MyVector *size;
	float angle;

	Wall(MyVector *location, MyVector *size, float angle)
		:location(location), size(size), angle(angle)
	{}

};