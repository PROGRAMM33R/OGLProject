
#include "Walls.hpp"

Walls::Walls(int countOfWalls, Config *cfg)
	:countOfWalls(countOfWalls), cfg(cfg) {

	this->wallsModel = new Model*[countOfWalls];
	this->walls = new vector<Wall*>();
	this->loadModels();

	float origin = 0.0;
	int angle = 0, randomResult = 0, sizeableConstant = 1;

	int arrayX[4] = {
		0, -300, 1000, -2500
	};

	int arrayZ[4] = {
		500, 1000, 2000, -2300
	};

	float angles[4] = {
		1.57, 0, 0, 1.57
	};

	MyVector *wallSize = new MyVector(0, 0, 0);
	MyVector *wallSize90 = new MyVector(1100, 0, 200);

	for (register int i = 0; i < countOfWalls; i++) {

		/*randomResult = ((double)rand() / (RAND_MAX)) + 1;
		if (randomResult == 1) {
			angle = 0;
		}
		else {
			angle = 0;
		}

		addWall(new Wall(
			new MyVector(
				(float)(rand() % cfg->BOID_CUBE_SIZE),
				0,
				(float)(rand() % cfg->BOID_CUBE_SIZE)
			),
			angle
			)
		);*/

		if (i == 0 || i == 3) {
			addWall(new Wall(
				new MyVector(
					arrayX[i],
					0,
					arrayZ[i]
				),
				wallSize90,
				angles[i]
			)
			);
		}
		else {
			addWall(new Wall(
				new MyVector(
					arrayX[i],
					0,
					arrayZ[i]
				),
				wallSize,
				angles[i]
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