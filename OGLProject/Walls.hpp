#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include "Model.hpp"
#include "Wall.hpp"
#include "Map.hpp"
#include "MyVector.hpp"

using namespace std;

class Shader;
class Walls {

private:
	int countOfWalls;
	vector<Wall*> *walls;
	Model **wallsModel;
	Model *exitModel;
	vector<Wall*> *pathToFind;
	Config *cfg;

	void loadModels(void);
	inline void addWall(Wall *w);

public:
	vector<glm::vec3> *generatePositions;
	map<int, MyVector*> exitPositions;

	Walls(Map *map, Config *cfg);
	~Walls() {}

	void drawWalls(Shader *shader);
	Wall *get(int i) const;
	int size(void) const;

};