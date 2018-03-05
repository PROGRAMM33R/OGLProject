#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include "Model.hpp"
#include "Wall.hpp"
#include "Map.hpp"
#include "MyVector.hpp"
#include "Controls.hpp"
#include "InstanceStorage.hpp"

using namespace std;

class Shader;
class Walls {

private:
	int countOfWalls, countOfFloors;
	vector<Wall*> *walls;
	vector<Wall*> *floors;
	Model **wallsModel;
	Model **floorsModel;
	Model *exitModel;
	vector<Wall*> *pathToFind;
	Config *cfg;
	int floor;
	float sizeX, sizeY;

	void loadModels(void);
	inline void addWall(Wall *w);

	InstanceStorage *ISWall;
	InstanceStorage *ISFloor;
	InstanceStorage *ISPath;

	int isInArray(char arr[], int size, char c);

public:
	vector<glm::vec3> *generatePositions;
	map<int, MyVector*> exitPositions;
	const float wallDiferencial = 250;
	const int floorDiferencial = 570;
	Controls *controls;
	bool labyrint = false;

	Walls(Map *map, Config *cfg, Controls *controls);
	~Walls() {}

	void drawWalls(Shader *shader);
	Wall *get(int i) const;
	int size(void) const;

};