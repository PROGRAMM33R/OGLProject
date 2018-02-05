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
	Wall *exit;
	Config *cfg;

	void loadModels(void);

public:
	glm::vec3 generatePosition;
	MyVector *exitPosition;

	Walls(Map *map, Config *cfg);
	~Walls() {}

	void addWall(Wall *w);
	void drawWalls(Shader *shader);
	Wall *get(int i);
	int size(void);

};