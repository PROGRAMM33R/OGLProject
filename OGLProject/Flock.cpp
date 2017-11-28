
#include "Flock.hpp"

Flock::Flock(int numberOfBoids, int numberOfPredators, int initialSpacingBetweenBoids, Config *cfg)
	:numberOfBoids(numberOfBoids), numberOfPredators(numberOfPredators), cfg(cfg){

	this->boidsModel = new Model*[numberOfBoids];
	this->flock = new vector<Boids*>();
	this->loadModels();

	for (register int i = 0; i < numberOfBoids; i++) {

		if (i < numberOfPredators) {
			addBoid(new Boids(
				(float)(rand() % initialSpacingBetweenBoids), 
				(float)(rand() % initialSpacingBetweenBoids),
				(float)(rand() % initialSpacingBetweenBoids),
				this->cfg,
				true
			)
			);
		}
		else {
			addBoid(new Boids(
				(float)(rand() % initialSpacingBetweenBoids),
				(float)(rand() % initialSpacingBetweenBoids),
				(float)(rand() % initialSpacingBetweenBoids),
				this->cfg
			)
			);
		}
		
	}

}

Flock::Flock(Config *cfg)
	: Flock(
		cfg->BOID_NUMBER_OF_BOIDS,
		cfg->BOID_NUMBER_OF_PREDATORS,
		cfg->BOID_GENERATE_SPACE,
		cfg
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

	for (register int i = 0; i < this->numberOfBoids; i++) {

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
	for (register int i = 0; i < this->numberOfBoids; i++) {
		this->flock->at(i)->run(flock);
		boidsModel[i]->Draw(shader, this->flock->at(i));
	}
}