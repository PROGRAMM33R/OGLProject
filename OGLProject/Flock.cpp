
#include "Flock.hpp"

Flock::Flock(int numberOfBoids, int numberOfPredators, int initialSpacingBetweenBoids, Config *cfg, Walls *walls)
	:numberOfBoids(numberOfBoids), numberOfPredators(numberOfPredators), cfg(cfg), walls(walls){

	this->boidsModel = new Model*[numberOfBoids * walls->generatePositions->size()];
	this->flock = new vector<Boids*>();
	this->loadModels();

	for (register unsigned int i = 0; i < numberOfBoids; ++i) {

		if (cfg->SCENE_TYPE == "3D") {
			if (i < numberOfPredators) {
				addBoid(new Boids(
					(float)(rand() % initialSpacingBetweenBoids),
					(float)(rand() % initialSpacingBetweenBoids),
					(float)(rand() % initialSpacingBetweenBoids),
					this->cfg,
					walls,
					true
				)
				);
			}
			else {
				addBoid(new Boids(
					(float)(rand() % initialSpacingBetweenBoids),
					(float)(rand() % initialSpacingBetweenBoids),
					(float)(rand() % initialSpacingBetweenBoids),
					this->cfg,
					walls,
					false
				)
				);
			}
		}
		else {
			for (register unsigned int j = 0; j < walls->generatePositions->size(); j++) {
				addBoid(new Boids(
					(float)(rand() % initialSpacingBetweenBoids) + walls->generatePositions->at(j).x,
					(float)(rand() % initialSpacingBetweenBoids) + walls->generatePositions->at(j).y,
					(float)(rand() % initialSpacingBetweenBoids) + walls->generatePositions->at(j).z,
					this->cfg,
					walls,
					false
				)
				);
			}
		}
		
	}

}

Flock::Flock(Config *cfg, Walls *walls)
	: Flock(
		cfg->BOID_NUMBER_OF_BOIDS,
		cfg->BOID_NUMBER_OF_PREDATORS,
		cfg->BOID_GENERATE_SPACE,
		cfg,
		walls
	)
{
	this->cfg = cfg;
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

	for (register unsigned int i = 0; i < this->numberOfBoids; ++i) {

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
	for (register unsigned int i = 0; i < this->numberOfBoids; ++i) {
		this->flock->at(i)->run(flock);
		boidsModel[i]->Draw(shader, DRAW_TYPE_BOIDS, this->flock->at(i));
	}
}