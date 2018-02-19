
#include "Walls.hpp"

Walls::Walls(Map *map, Config *cfg)
	: cfg(cfg) {

	this->countOfWalls = 0;
	this->countOfFloors = 0;

	for (int i = 0; i < map->map->size(); i++) {
		countOfWalls += map->map->at(i)->size();
	}

	this->wallsModel = new Model*[countOfWalls];
	this->walls = new vector<Wall*>();

	MyVector *wallSize = new MyVector(25, 0, 0);
	MyVector *wallSize90 = new MyVector(0, 0, 25);

	floor = 0;
	countOfWalls = 0;
	this->generatePositions = new vector<glm::vec3>();
	this->pathToFind = new vector<Wall*>();
	this->floors = new vector<Wall*>();

	sizeX = 0, sizeY = 0;
	int tmpJ = 0;

	std::map<int, MyVector*>::iterator it = exitPositions.begin();

	for (int i = 0, floorIndex = -1, len = map->map->size(); i < len; ++i) {

		if (floor != 0) {
			++floorIndex;
		}
		if (len > this->sizeX) {
			this->sizeX = len;
		}

		for (int j = 0, len2 = map->map->at(i)->size(); j < len2; ++j) {

			if (len2 > this->sizeY) {
				this->sizeY = len;
			}
			if (j == len2 - 1)
				tmpJ = j;

			if (map->map->at(i)->at(j) == '=') {
				floorIndex = -1;
				this->floors->push_back(new Wall(
					new MyVector(
						0,
						floor * floorDiferencial,
						0
					),
					new MyVector(
						tmpJ * wallDiferencial,
						-88,
						i * wallDiferencial
					),
					(float)0, 0, 0
				)
				);
				++floor;
				++this->countOfFloors;
			}

			if (map->map->at(i)->at(j) == '-' || map->map->at(i)->at(j) == '*') {

				addWall(new Wall(
					new MyVector(
						0 + (j * wallDiferencial),
						floor * floorDiferencial,
						floor == 0 ? 0 + (i * wallDiferencial) : 0 + (floorIndex * wallDiferencial)
					),
					wallSize,
					(float)0, 0, floor
				)
				);
				++countOfWalls;
					
			}
			
			if (map->map->at(i)->at(j) == '|' || map->map->at(i)->at(j) == '*') {

				addWall(new Wall(
					new MyVector(
						0 + (j * wallDiferencial),
						floor * floorDiferencial,
						floor == 0 ? 0 + (i * wallDiferencial) : 0 + (floorIndex * wallDiferencial)
					),
					wallSize90,
					(float)1.57, 0, floor
				)
				);
				++countOfWalls;

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
				this->pathToFind->push_back(new Wall(
					exitPositions.at(1000),
					wallSize90,
					0
				));
			}

			if (map->map->at(i)->at(j) == 'A' || map->map->at(i)->at(j) == 'a') {
				int index = map->map->at(i)->at(j) == 'A' ? 2 : 1;
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

			if (map->map->at(i)->at(j) == 'B' || map->map->at(i)->at(j) == 'b') {
				int index = map->map->at(i)->at(j) == 'B' ? 4 : 3;
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

			if (map->map->at(i)->at(j) == 'C' || map->map->at(i)->at(j) == 'c') {
				int index = map->map->at(i)->at(j) == 'C' ? 6 : 5;
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

			if (map->map->at(i)->at(j) == 'D' || map->map->at(i)->at(j) == 'd') {
				int index = map->map->at(i)->at(j) == 'D' ? 8 : 7;
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

			if (map->map->at(i)->at(j) == 'E' || map->map->at(i)->at(j) == 'e') {
				int index = map->map->at(i)->at(j) == 'E' ? 10 : 9;
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

			if (map->map->at(i)->at(j) == 'F' || map->map->at(i)->at(j) == 'f') {
				int index = map->map->at(i)->at(j) == 'F' ? 12 : 11;
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


		}

	}
	this->floorsModel = new Model*[this->countOfFloors];

	floor = 0;

	for (int i = 0, floorIndex = -1, len = map->map->size(); i < len; ++i) {

		if (floor != 0) {
			++floorIndex;
		}

		for (int j = 0, len2 = map->map->at(i)->size(); j < len2; ++j) {

			if (map->map->at(i)->at(j) == '=') {
				++floor;
				floorIndex = -1;
			}

			if (map->map->at(i)->at(j) == '+') {

				if (i > 0 && j > 0 && map->map->at(i)->at(j - 1) != NULL && map->map->at(i - 1)->at(j) != NULL) {
					if (map->map->at(i)->at(j - 1) == '-' && map->map->at(i - 1)->at(j) == '|') {

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial) - 52,
								floor * floorDiferencial,
								floor == 0 ? 0 + (i * wallDiferencial) : 0 + (floorIndex * wallDiferencial)
							),
							wallSize,
							(float)0, 25, floor
						)
						);
						++countOfWalls;

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial),
								floor * floorDiferencial,
								floor == 0 ? 0 + (i * wallDiferencial) - 40 : 0 + (floorIndex * wallDiferencial) - 40
							),
							wallSize90,
							(float)1.57, 25, floor
						)
						);
						++countOfWalls;
					}
				}

				if ((i > 0) && (j < map->map->at(i)->size() - 1) && map->map->at(i)->at(j + 1) != NULL && map->map->at(i - 1)->at(j) != NULL) {
					if (map->map->at(i)->at(j + 1) == '-' && map->map->at(i - 1)->at(j) == '|') {
						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial) + 52,
								floor * floorDiferencial,
								floor == 0 ? 0 + (i * wallDiferencial) : 0 + (floorIndex * wallDiferencial)
							),
							wallSize,
							(float)0, 25, floor
						)
						);
						++countOfWalls;

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial),
								floor * floorDiferencial,
								floor == 0 ? 0 + (i * wallDiferencial) - 40 : 0 + (floorIndex * wallDiferencial) - 40
							),
							wallSize90,
							(float)1.57, 25, floor
						)
						);
						++countOfWalls;
					}
				}

				// full condition to check all rules
				//if ((i > 0 && j > 0) && (i < map->map->size() - 1) && (j < map->map->at(i)->size() - 1)) {

				if ((j > 0) && (i < map->map->size() - 1) && map->map->at(i)->at(j - 1) != NULL && map->map->at(i + 1)->at(j) != NULL) {
					if (map->map->at(i)->at(j - 1) == '-' && map->map->at(i + 1)->at(j) == '|') {
						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial) - 52,
								floor * floorDiferencial,
								floor == 0 ? 0 + (i * wallDiferencial) : 0 + (floorIndex * wallDiferencial)
							),
							wallSize,
							(float)0, 25, floor
						)
						);
						++countOfWalls;

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial),
								floor * floorDiferencial,
								floor == 0 ? 0 + (i * wallDiferencial) + 78 : 0 + (floorIndex * wallDiferencial) + 78
							),
							wallSize90,
							(float)1.57, 15, floor
						)
						);
						++countOfWalls;
					}
				}

				if ((i < map->map->size() - 1) && (j < map->map->at(i)->size() - 1) && map->map->at(i)->at(j + 1) != NULL && map->map->at(i + 1)->at(j) != NULL) {
					if (map->map->at(i)->at(j + 1) == '-' && map->map->at(i + 1)->at(j) == '|') {
						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial) + 52,
								floor * floorDiferencial,
								floor == 0 ? 0 + (i * wallDiferencial) : 0 + (floorIndex * wallDiferencial)
							),
							wallSize,
							(float)0, 25, floor
						)
						);
						++countOfWalls;

						addWall(new Wall(
							new MyVector(
								0 + (j * wallDiferencial),
								floor * floorDiferencial,
								floor == 0 ? 0 + (i * wallDiferencial) + 78 : 0 + (floorIndex * wallDiferencial) + 78
							),
							wallSize90,
							(float)1.57, 15, floor
						)
						);
						++countOfWalls;
					}
				}

			}

		}

	}

	this->loadModels();

}

void Walls::addWall(Wall *w)
{
	this->walls->push_back(w);
}

void Walls::loadModels(void) {

	Model *tmpWallModel = new Model(this->cfg->OBJ_WALL, this->cfg);
	Model *tmpFloorModel = new Model(this->cfg->OBJ_SURFACE, this->cfg);

	for (int i = 0; i < this->countOfWalls; ++i) {
		this->wallsModel[i] = new Model(*tmpWallModel);
	}

	for (int i = 0; i < this->countOfFloors; ++i) {
		this->floorsModel[i] = new Model(*tmpFloorModel);
	}

	this->exitModel = new Model(this->cfg->OBJ_EXIT, this->cfg);

}

void Walls::drawWalls(Shader *shader)
{
	for (int i = 0; i < this->countOfWalls; ++i) {
		this->wallsModel[i]->Draw(shader, DRAW_TYPE_WALL, NULL, this->walls->at(i));		
	}

	for (int i = 0; i < this->countOfFloors; ++i) {
		this->floorsModel[i]->Draw(shader, DRAW_TYPE_FLOOR, NULL, this->floors->at(i));
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