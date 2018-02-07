#pragma once

#include "Std.hpp"
#include "MyVector.hpp"

class Wall {

private:

public:
	MyVector *location;
	MyVector *size;
	float angle;
	int meshSize;

	Wall(MyVector *location, MyVector *size, float angle, int meshSize = 0)
		:location(location), size(size), angle(angle), meshSize(meshSize)
	{}

};