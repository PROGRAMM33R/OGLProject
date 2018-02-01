
#include "Walls.hpp"

Walls::Walls(int countOfWalls, Config *cfg)
	:countOfWalls(countOfWalls), cfg(cfg) {

	this->wallsModel = new Model*[countOfWalls];
	this->walls = new vector<Wall*>();
	this->loadModels();

	MyVector *wallSize = new MyVector(500, 0, 0);
	MyVector *wallSize90 = new MyVector(0, 0, 500);

	bool flipFlop = false;
	float divide = 2.5;

	for (register int i = 0; i < countOfWalls; i++) {

		if (!flipFlop) {
			flipFlop = true;

			addWall(new Wall(
				new MyVector(
					(rand() % cfg->BOID_CUBE_SIZE) / divide,
					0,
					(rand() % cfg->BOID_CUBE_SIZE) / divide
				),
				wallSize,
				0
			)
			);

		}
		else {
			flipFlop = false;

			addWall(new Wall(
				new MyVector(
					(rand() % cfg->BOID_CUBE_SIZE) / divide,
					0,
					(rand() % cfg->BOID_CUBE_SIZE) / divide
				),
				wallSize90,
				1.57
			)
			);
		}

	}

}

void Walls::addWall(Wall *w)
{
	this->walls->push_back(w);
}

Walls::Walls(Config *cfg)
	: Walls(
		cfg->SCENE_COUNT_OF_WALLS,
		cfg
	)
{
	this->cfg = cfg;
}

void Walls::loadModels(void) {

	Model *tmpWallModel = new Model(this->cfg->OBJ_WALL, this->cfg);

	for (register int i = 0; i < this->countOfWalls; i++) {

		this->wallsModel[i] = new Model(*tmpWallModel);

	}

}

void Walls::drawWalls(Shader *shader)
{
	for (register int i = 0; i < this->countOfWalls; i++) {
		wallsModel[i]->Draw(shader, DRAW_TYPE_WALL, NULL, this->walls->at(i));
	}
}

Wall *Walls::get(int i) {
	return this->walls->at(i);
}

int Walls::size(void) {
	return this->walls->size();
}