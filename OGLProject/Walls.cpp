
#include "Walls.hpp"

Walls::Walls(Map *map, Config *cfg, Controls *controls)
	: cfg(cfg), controls(controls) {

	this->countOfWalls = 0;
	this->countOfFloors = 0;

	for (int i = 0; i < map->map->size(); i++) {
		countOfWalls += map->map->at(i)->size();
	}

	this->wallsModel = new Model*[countOfWalls];
	this->walls = new vector<Wall*>();

	MyVector *wallSize = new MyVector(25, 0, 0);
	MyVector *wallSize90 = new MyVector(0, 0, 25);

	this->floor = 0;
	countOfWalls = 0;
	this->generatePositions = new vector<glm::vec3>();
	this->pathToFind = new vector<Wall*>();
	this->floors = new vector<Wall*>();

	sizeX = 0.0, sizeY = 0.0;
	bool nextFloor = false;
	bool haveFirstWall = false, haveFirstWallJ = false;
	int firstX = 0, firstY = 0, lastX = 0, lastY = 0, firstWall = 0, firstWallJ = 0;

	std::map<int, MyVector*>::iterator it = exitPositions.begin();

	char exitPoints[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	int exitPointsIndex = 1;

	for (int i = 0, floorIndex = -1, len = map->map->size(); i < len; ++i) {

		if (this->floor != 0) {
			++floorIndex;
		}
		
		for (int j = 0, len2 = map->map->at(i)->size(); j < len2; ++j) {

			if (map->map->at(i)->at(j) == '=') {
				floorIndex = -1;
				++this->floor;
				++this->countOfFloors;
				nextFloor = true;
				haveFirstWall = false; haveFirstWallJ = false;
				firstWall = 0; firstWallJ = 0;
				firstX = 0; firstY = 0; lastY = 0;
			}

			if (nextFloor) {

				bool firstCross = false;
				nextFloor = false;
				int tmpI = i;
				for (int ii = ++tmpI, generationZ = 0, lenii = map->map->size(); ii < lenii; ++ii, ++generationZ) {
					for (int jj = 0, len2jj = map->map->at(ii)->size(); jj < len2jj; ++jj) {

						if (map->map->at(ii)->at(jj) != '/') {

							if ((map->map->at(ii)->at(jj) == '+' || map->map->at(ii)->at(jj) == '|' || map->map->at(ii)->at(jj) == '-') && !firstCross) {
								firstCross = true;
								firstX = ii;
								firstY = jj;
								if (!haveFirstWallJ) {
									firstWallJ = jj;
									haveFirstWallJ = true;
								}
							}

							if (map->map->at(ii)->at(jj) == '+' || map->map->at(ii)->at(jj) == '|' || map->map->at(ii)->at(jj) == '-') {
								lastX = ii;
								lastY = jj;
								if (!haveFirstWallJ) {
									firstWallJ = jj;
									haveFirstWallJ = true;
								}
							}

						}
						else {

							this->sizeX = (float)(lastX - firstX);
							this->sizeY = (float)(lastY - firstY);

							this->floors->push_back(new Wall(
								new MyVector(
									firstWallJ * wallDiferencial,
									floor * floorDiferencial,
									firstWall * wallDiferencial
								),
								new MyVector(
									this->sizeX * wallDiferencial,
									0,
									this->sizeY * wallDiferencial
								),
								(float)0, 0, this->floor
							)
							);

							lastX = ii + 1;
							lenii = -1;
							break;
						}

						if (map->map->at(ii)->at(jj) == 'G' || map->map->at(ii)->at(jj) == 'g') {
							this->generatePositions->push_back(
								glm::vec3(
									jj * wallDiferencial, 
									floor * floorDiferencial, 
									(firstWall + generationZ) * wallDiferencial
								)
							);
						}

					}
				}

			}

			if (map->map->at(i)->at(j) == '-' || map->map->at(i)->at(j) == '*') {

				addWall(new Wall(
					new MyVector(
						0 + (j * wallDiferencial),
						floor * floorDiferencial,
						floor == 0 ? 0 + (i * wallDiferencial) : 0 + (floorIndex * wallDiferencial)
					),
					wallSize,
					(float)0, 0, this->floor
				)
				);
				++countOfWalls;

				if (!haveFirstWall) {
					firstWall = i;
					haveFirstWall = true;
				}
					
			}
			
			if (map->map->at(i)->at(j) == '|' || map->map->at(i)->at(j) == '*') {

				addWall(new Wall(
					new MyVector(
						0 + (j * wallDiferencial),
						floor * floorDiferencial,
						floor == 0 ? 0 + (i * wallDiferencial) : 0 + (floorIndex * wallDiferencial)
					),
					wallSize90,
					(float)1.57, 0, this->floor
				)
				);
				++countOfWalls;

				if (!haveFirstWall) {
					firstWall = i;
					haveFirstWall = true;
				}

			}

			if (this->floor == 0) {
				if (map->map->at(i)->at(j) == 'G' || map->map->at(i)->at(j) == 'g') {
					this->generatePositions->push_back(
						glm::vec3(j * wallDiferencial, floor * floorDiferencial, i * wallDiferencial)
					);
				}
			}

			if (isdigit(map->map->at(i)->at(j))) {
				int index = map->map->at(i)->at(j) - '0';
				exitPositions.insert(
					it, 
					std::pair<int, MyVector*>(
						index, 
						new MyVector(j * wallDiferencial, floor * floorDiferencial, i * wallDiferencial)
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
						new MyVector(j * wallDiferencial, floor * floorDiferencial, i * wallDiferencial)
					)
				);
				this->pathToFind->push_back(new Wall(
					exitPositions.at(1000),
					wallSize90,
					0
				));
			}

			for (
				int charMapIndex = 0, exitPointsIndex = 1, len = (sizeof(exitPoints) / sizeof(*exitPoints)); 
				charMapIndex < len; 
				++charMapIndex, exitPointsIndex += 2
				) {

				if (map->map->at(i)->at(j) == exitPoints[charMapIndex] || map->map->at(i)->at(j) == tolower(exitPoints[charMapIndex])) {
					int index = map->map->at(i)->at(j) == exitPoints[charMapIndex] ? (exitPointsIndex + 1) : exitPointsIndex;
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
	this->ISWall = new InstanceStorage(NULL, DRAW_TYPE_WALL, NULL, NULL);
	this->ISFloor = new InstanceStorage(NULL, DRAW_TYPE_FLOOR, NULL, NULL);
	this->ISPath = new InstanceStorage(NULL, DRAW_TYPE_EXIT, NULL, NULL);

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
	this->ISWall->shader = shader;
	this->ISFloor->shader = shader;
	this->ISFloor->activeFloor = controls->activatedFloor;
	this->ISFloor->transparency = 0.1;
	this->ISWall->activeFloor = controls->activatedFloor;
	this->ISWall->transparency = 0.1;
	this->ISPath->shader = shader;

	for (int i = 0; i < this->countOfWalls; ++i) {
		this->ISWall->walls = this->walls->at(i);
		this->wallsModel[i]->Draw(this->ISWall);		
	}

	for (int i = 0; i < this->countOfFloors; ++i) {
		this->ISFloor->walls = this->floors->at(i);
		this->floorsModel[i]->Draw(this->ISFloor);
	}

	for (int i = 0, len = this->pathToFind->size(); i < len; ++i) {
		this->ISPath->walls = this->pathToFind->at(i);
		this->exitModel->Draw(this->ISPath);
	}
}

Wall *Walls::get(int i) const {
	return this->walls->at(i);
}

int Walls::size(void) const {
	return this->walls->size();
}