#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Shader;
class Boids;
class Wall;
class MyVector;
class InstanceStorage {

private:

public:
	Shader * shader;
	int objType;
	Boids *Boidss;
	Wall *walls;
	MyVector *exitPathPosition;
	int floorDiferencial;
	bool isExitPath;

	int activeFloor = 0;
	float transparency = 0.0;

	InstanceStorage(
		Shader *shader = NULL, 
		int objType = 0, 
		Boids *Boidss = NULL, 
		Wall *walls = NULL
	)
		: shader(shader), objType(objType), Boidss(Boidss), walls(walls)
	{}

	InstanceStorage()
		: shader(NULL), objType(0), Boidss(NULL), walls(NULL)
	{}

	~InstanceStorage() {}

};