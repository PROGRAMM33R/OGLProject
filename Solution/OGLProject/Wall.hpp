#pragma once

#include "Object.hpp"
#include "MyVector.hpp"

class Wall : public Object {

private:

public:
	int meshSize, floor;
	int meshSizeX, meshSizeZ;

	Wall(MyVector *location, MyVector *size, float angle, int meshSize = 0, int floor = 0){

		this->location = location;
		this->size = size;
		this->angle = angle;
		this->floor = floor;
		this->meshSize = meshSize;

		meshSizeX = size->vec.x;
		meshSizeZ = size->vec.z;
		
	}
	
	Wall() {
		Object();
		this->meshSize = 0;
	}

};