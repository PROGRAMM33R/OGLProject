
#include "Walls.hpp"

Walls::Walls(Map *map, Config *cfg)
	: cfg(cfg) {

	countOfWalls = 0;

	for (int i = 0; i < map->map->size(); i++) {
		countOfWalls += map->map->at(i)->size();
	}

	this->wallsModel = new Model*[countOfWalls];
	this->walls = new vector<Wall*>();
	this->loadModels();

	MyVector *wallSize = new MyVector(25, 0, 0);
	MyVector *wallSize90 = new MyVector(0, 0, 25);

	float wallDiferencial = 250;

	countOfWalls = 0;
	this->generatePositions = new vector<glm::vec3>();
	this->pathToFind = new vector<Wall*>();

	std::map<int, MyVector*>::iterator it = exitPositions.begin();

	for (int i = 0, len = map->map->size(); i < len; ++i) {

		for (int j = 0, len2 = map->map->at(i)->size(); j < len2; ++j) {

			if (map->map->at(i)->at(j) == '-' || map->map->at(i)->at(j) == '*') {

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
			
			if (map->map->at(i)->at(j) == '|' || map->map->at(i)->at(j) == '*') {

				addWall(new Wall(
					new MyVector(
						0 + (j * wallDiferencial),
						0,
						0 + (i * wallDiferencial)
					),
					wallSize90,
					(float)1.57
				)
				);
				countOfWalls++;

			}

			if (map->map->at(i)->at(j) == 'G' || map->map->at(i)->at(j) == 'g') {
				this->generatePositions->push_back( 
					glm::vec3(j * wallDiferencial, 0, i * wallDiferencial) 
				);
			}

			if (isdigit(map->map->at(i)->at(j))) {
				int index = map->map->at(i)->at(j) - '0';
				exitPositions.insert(
					it, 
					std::pair<int, MyVector*>(
						index, 
						new MyVector(j * wallDiferencial, 0, i * wallDiferencial)
					)
				); 

				this->pathToFind->push_back(new Wall(
					exitPositions.at(index),
					wallSize90,
					0
				));
			}
			else if (map->map->at(i)->at(j) == 'F') {
				exitPositions.insert(
					it,
					std::pair<int, MyVector*>(
						1000,
						new MyVector(j * wallDiferencial, 0, i * wallDiferencial)
					)
				);
			}

		}

	}

	for (int i = 0, len = map->map->size(); i < len; ++i) {

		for (int j = 0, len2 = map->map->at(i)->size(); j < len2; ++j) {

			if (map->map->at(i)->at(j) == '+') {

				if (i > 0 && j > 0 && map->map->at(i)->at(j - 1) != NULL && map->map->at(i - 1)->at(j) != NULL) {
					if (map->map->at(i)->at(j - 1) == '-' && map->map->at(i - 1)->at(j) == '|') {

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial) - 52,
								0,
								0 + (i * wallDiferencial)
							),
							wallSize,
							(float)0, 25
						)
						);
						countOfWalls++;

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial),
								0,
								0 + (i * wallDiferencial) - 40
							),
							wallSize90,
							(float)1.57, 25
						)
						);
						countOfWalls++;
					}
				}

				if ((i > 0) && (j < map->map->at(i)->size() - 1) && map->map->at(i)->at(j + 1) != NULL && map->map->at(i - 1)->at(j) != NULL) {
					if (map->map->at(i)->at(j + 1) == '-' && map->map->at(i - 1)->at(j) == '|') {
						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial) + 52,
								0,
								0 + (i * wallDiferencial)
							),
							wallSize,
							(float)0, 25
						)
						);
						countOfWalls++;

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial),
								0,
								0 + (i * wallDiferencial) - 40
							),
							wallSize90,
							(float)1.57, 25
						)
						);
						countOfWalls++;
					}
				}

				// full condition to check all rules
				//if ((i > 0 && j > 0) && (i < map->map->size() - 1) && (j < map->map->at(i)->size() - 1)) {

				if ((j > 0) && (i < map->map->size() - 1) && map->map->at(i)->at(j - 1) != NULL && map->map->at(i + 1)->at(j) != NULL) {
					if (map->map->at(i)->at(j - 1) == '-' && map->map->at(i + 1)->at(j) == '|') {
						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial) - 52,
								0,
								0 + (i * wallDiferencial)
							),
							wallSize,
							(float)0, 25
						)
						);
						countOfWalls++;

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial),
								0,
								0 + (i * wallDiferencial) + 78
							),
							wallSize90,
							(float)1.57, 15
						)
						);
						countOfWalls++;
					}
				}

				if ((i < map->map->size() - 1) && (j < map->map->at(i)->size() - 1) && map->map->at(i)->at(j + 1) != NULL && map->map->at(i + 1)->at(j) != NULL) {
					if (map->map->at(i)->at(j + 1) == '-' && map->map->at(i + 1)->at(j) == '|') {
						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial) + 52,
								0,
								0 + (i * wallDiferencial)
							),
							wallSize,
							(float)0, 25
						)
						);
						countOfWalls++;

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial),
								0,
								0 + (i * wallDiferencial) + 78
							),
							wallSize90,
							(float)1.57, 15
						)
						);
						countOfWalls++;
					}
				}

			}

		}

	}

	this->pathToFind->push_back(new Wall(
		exitPositions.at(1000),
		wallSize90,
		0
	));

}

void Walls::addWall(Wall *w)
{
	this->walls->push_back(w);
}

void Walls::loadModels(void) {

	Model *tmpWallModel = new Model(this->cfg->OBJ_WALL, this->cfg);

	for (int i = 0; i < this->countOfWalls; ++i) {

		this->wallsModel[i] = new Model(*tmpWallModel);

	}

	this->exitModel = new Model(this->cfg->OBJ_EXIT, this->cfg);

}

void Walls::drawWalls(Shader *shader)
{
	for (int i = 0; i < this->countOfWalls; ++i) {
		this->wallsModel[i]->Draw(shader, DRAW_TYPE_WALL, NULL, this->walls->at(i));
	}
	for (int i = 0, len = this->pathToFind->size(); i < len; ++i) {
		this->exitModel->Draw(shader, DRAW_TYPE_EXIT, NULL, this->pathToFind->at(i));
	}
}

Wall *Walls::get(int i) const {
	return this->walls->at(i);
}

int Walls::size(void) const {
	return this->walls->size();
}