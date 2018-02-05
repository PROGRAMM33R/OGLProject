
#include "Walls.hpp"

Walls::Walls(Map *map, Config *cfg)
	: cfg(cfg) {

	countOfWalls = 0;

	for (register unsigned int i = 0; i < map->map->size(); i++) {
		countOfWalls += map->map->at(i)->size();
	}

	this->wallsModel = new Model*[countOfWalls];
	this->walls = new vector<Wall*>();
	this->loadModels();

	MyVector *wallSize = new MyVector(200, 0, 0);
	MyVector *wallSize90 = new MyVector(0, 0, 200);

	float wallDiferencial = 450;

	countOfWalls = 0;
	generatePosition = glm::vec3(0, 0, 0);
	exitPosition = new MyVector();

	for (register unsigned int i = 0; i < map->map->size(); i++) {

		for (register unsigned int j = 0; j < map->map->at(i)->size(); j++) {

			if (map->map->at(i)->at(j) == '-' || map->map->at(i)->at(j) == '+') {

				addWall(new Wall(
					new MyVector(
						0 + (j * wallDiferencial),
						0,
						0 + (i * wallDiferencial)
					),
					wallSize,
					(float)0
				)
				);
				countOfWalls++;
					
			}
			
			if (map->map->at(i)->at(j) == '|' || map->map->at(i)->at(j) == '+') {

				addWall(new Wall(
					new MyVector(
						0 + (j * wallDiferencial),
						0,
						0 + (i * (wallDiferencial + 30))
					),
					wallSize90,
					(float)1.57
				)
				);
				countOfWalls++;

			}

			if (map->map->at(i)->at(j) == 'G' || map->map->at(i)->at(j) == 'g') {
				generatePosition = glm::vec3(j * wallDiferencial, 0, i * wallDiferencial);
			}

			if (map->map->at(i)->at(j) == 'F' || map->map->at(i)->at(j) == 'f') {
				exitPosition->set(j * wallDiferencial, 0, i * wallDiferencial);
			}

		}

	}

	this->exit = new Wall(
		new MyVector(
			exitPosition->vec.x,
			exitPosition->vec.y,
			exitPosition->vec.z
		),
		wallSize90,
		0
	);

}

void Walls::addWall(Wall *w)
{
	this->walls->push_back(w);
}

void Walls::loadModels(void) {

	Model *tmpWallModel = new Model(this->cfg->OBJ_WALL, this->cfg);

	for (register int i = 0; i < this->countOfWalls; i++) {

		this->wallsModel[i] = new Model(*tmpWallModel);

	}

	this->exitModel = new Model(this->cfg->OBJ_EXIT, this->cfg);

}

void Walls::drawWalls(Shader *shader)
{
	for (register int i = 0; i < this->countOfWalls; i++) {
		this->wallsModel[i]->Draw(shader, DRAW_TYPE_WALL, NULL, this->walls->at(i));
	}
	this->exitModel->Draw(shader, DRAW_TYPE_EXIT, NULL, this->exit);
}

Wall *Walls::get(int i) {
	return this->walls->at(i);
}

int Walls::size(void) {
	return this->walls->size();
}