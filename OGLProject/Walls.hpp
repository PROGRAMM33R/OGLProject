#pragma once

#include "Std.hpp"
#include "Model.hpp"
#include "Wall.hpp"
#include "Map.hpp"
#include "MyVector.hpp"

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

public:
	vector<glm::vec3> *generatePositions;
	map<int, MyVector*> exitPositions;

	Walls(Map *map, Config *cfg);
	~Walls() {}

	void addWall(Wall *w);
	void drawWalls(Shader *shader);
	Wall *get(int i) const;
	int size(void) const;

};