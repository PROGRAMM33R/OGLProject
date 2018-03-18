
#include "Flock.hpp"

Flock::Flock(Config *cfg, Walls *walls)
	:cfg(cfg), walls(walls){

	numberOfBoids = this->cfg->BOID_NUMBER_OF_BOIDS;
	numberOfPredators = this->cfg->BOID_NUMBER_OF_PREDATORS;

	if (this->cfg->SCENE_TYPE == "3D") {
		this->boidsModel = new Model*[this->numberOfBoids + this->numberOfPredators];
	}
	else {
		this->boidsModel = new Model*[this->numberOfBoids * walls->generatePositions->size()];
	}
	
	this->flock = new vector<Boids*>();
	this->loadModels();

	for (int i = 0; i < (this->numberOfBoids + this->numberOfPredators); ++i) {

		if (this->cfg->SCENE_TYPE == "3D") {
			if (i < this->numberOfPredators) {
				addBoid(new Boids(
					new MyVector(
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE),
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE),
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE)
					),
					this->cfg,
					NULL,
					true, 0
				)
				);
			}
			else {
				addBoid(new Boids(
					new MyVector(
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE),
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE),
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE)
					),
					this->cfg,
					NULL,
					false, 0
				)
				);
			}
		}
		else {
			for (int j = 0, val = walls->generatePositions->size(); j < val; ++j) {

				addBoid(new Boids(
					new MyVector(
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE) + walls->generatePositions->at(j).x,
						walls->generatePositions->at(j).y,
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE) + walls->generatePositions->at(j).z
					),
					this->cfg,
					walls,
					false, (walls->generatePositions->at(j).y / walls->floorDiferencial)
				)
				);

			}
		}
		
	}

	this->ISBoid = new InstanceStorage(NULL, DRAW_TYPE_BOIDS, NULL, NULL);
	this->ISPredator = new InstanceStorage(NULL, DRAW_TYPE_PREDATOR, NULL, NULL);

}

void Flock::addBoid(Boids *b)
{
	this->flock->push_back(b);
}

void Flock::loadModels(void) {

	Model *tmpBoidsModel = NULL, *tmpBoidsModelPredator = NULL;
	if (this->numberOfBoids >= 1) {
		tmpBoidsModel = new Model(this->cfg->OBJ_BOID, this->cfg);
	}
	if (this->numberOfPredators >= 1) {
		tmpBoidsModelPredator = new Model(this->cfg->OBJ_PREDATOR, this->cfg);
	}

	for (int i = 0; i < (this->numberOfBoids + this->numberOfPredators); ++i) {

		if (i < this->numberOfPredators) {
			if (tmpBoidsModelPredator != NULL)
				this->boidsModel[i] = new Model(*tmpBoidsModelPredator);
		}
		else {
			if (tmpBoidsModel != NULL)
				this->boidsModel[i] = new Model(*tmpBoidsModel);
		}

	}

}

void Flock::flocking(Shader *shader)
{
	this->ISBoid->shader = this->ISPredator->shader = shader;
	this->ISBoid->transparency = this->ISPredator->transparency = 0.1;
	this->ISBoid->floorDiferencial = this->ISPredator->floorDiferencial = walls->floorDiferencial;

	for (int i = 0; i < (this->numberOfBoids + this->numberOfPredators); ++i) {

		this->flock->at(i)->run(flock);
		this->ISBoid->Boidss = this->flock->at(i);
		this->ISBoid->activeFloor = this->walls->controls->activatedFloor;
		boidsModel[i]->Draw(this->ISBoid);

	}

}