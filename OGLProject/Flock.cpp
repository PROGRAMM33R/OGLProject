
#include "Flock.hpp"

Flock::Flock(int numberOfBoids, int numberOfPredators, int initialSpacingBetweenBoids)
	:numberOfBoids(numberOfBoids), numberOfPredators(numberOfPredators){

	this->boidsModel = new Model*[numberOfBoids];
	this->flock = new vector<Boids*>();
	this->loadModels();

	for (register int i = 0; i < numberOfBoids; i++) {

		if (i < numberOfPredators) {
			addBoid(new Boids(
				rand() % initialSpacingBetweenBoids, rand() % initialSpacingBetweenBoids, true)
			);
		}
		else {
			addBoid(new Boids(
				rand() % initialSpacingBetweenBoids, rand() % initialSpacingBetweenBoids)
			);
		}
		
	}

}

Flock::Flock() 
	: Flock(
		Config::NUMBER_OF_BOIDS, 
		Config::NUMBER_OF_PREDATORS, 
		Config::GENERATE_SPACE
	) 
{}

void Flock::addBoid(Boids *b)
{
	this->flock->push_back(b);
}

void Flock::loadModels(void) {

	Model *tmpBoidsModel = NULL, *tmpBoidsModelPredator = NULL;
	if (this->numberOfBoids >= 1) {
		tmpBoidsModel = new Model(Config::OBJ_BOID);
	}
	else if (this->numberOfPredators >= 1) {
		tmpBoidsModelPredator = new Model(Config::OBJ_PREDATOR);
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

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking(Shader *shader)
{
	for (register int i = 0; i < this->numberOfBoids; i++) {
		this->flock->at(i)->run(flock);
		boidsModel[i]->Draw(shader, this->flock->at(i));
	}
}