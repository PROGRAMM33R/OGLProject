#pragma once

#include "Std.hpp"
#include "Model.hpp"
#include "Wall.hpp"
#include "MyVector.hpp"

class Shader;
class Walls {

private:
	int countOfWalls;
	vector<Wall*> *walls;
	Model **wallsModel;
	Config *cfg;

	void loadModels(void);

public:
	Walls(int countOfWalls, Config *cfg);
	Walls(Config *cfg);
	~Walls() {}

	void addWall(Wall *w);
	void drawWalls(Shader *shader);
	Wall *get(int i);
	int size(void);

};