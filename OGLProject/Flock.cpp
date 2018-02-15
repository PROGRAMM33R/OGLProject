
#include "Flock.hpp"

Flock::Flock(Config *cfg, Walls *walls)
	:cfg(cfg), walls(walls){

	numberOfBoids = this->cfg->BOID_NUMBER_OF_BOIDS;
	numberOfPredators = this->cfg->BOID_NUMBER_OF_PREDATORS;

	this->boidsModel = new Model*[this->cfg->BOID_NUMBER_OF_BOIDS * walls->generatePositions->size()];
	this->flock = new vector<Boids*>();
	this->loadModels();

	for (int i = 0; i < cfg->BOID_NUMBER_OF_BOIDS; ++i) {

		if (this->cfg->SCENE_TYPE == "3D") {
			if (i < cfg->BOID_NUMBER_OF_PREDATORS) {
				addBoid(new Boids(
					new MyVector(
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE),
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE),
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE)
					),
					this->cfg,
					walls,
					true
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
					walls,
					false
				)
				);
			}
		}
		else {
			for (int j = 0, val = walls->generatePositions->size(); j < val; ++j) {
				addBoid(new Boids(
					new MyVector(
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE) + walls->generatePositions->at(j).x,
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE) + walls->generatePositions->at(j).y,
						(float)(rand() % this->cfg->BOID_GENERATE_SPACE) + walls->generatePositions->at(j).z
					),
					this->cfg,
					walls,
					false
				)
				);
			}
		}
		
	}

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

	for (int i = 0; i < this->numberOfBoids; ++i) {

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
	for (int i = 0; i < this->numberOfBoids; ++i) {
		this->flock->at(i)->run(flock);
		boidsModel[i]->Draw(shader, DRAW_TYPE_BOIDS, this->flock->at(i));
	}
}