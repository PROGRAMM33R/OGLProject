#pragma once

#include "Std.hpp"
#include "Boids.hpp"
#include "Model.hpp"

class Shader;
class Flock {

private:
	int numberOfBoids, numberOfPredators;
	vector<Boids*> *flock;
	Model **boidsModel;

	void loadModels(void);

public:
	
	Flock(int numberOfBoids, int numberOfPredators, int initialSpacingBetweenBoids);
	Flock();
	~Flock() {}
	
	void addBoid(Boids *b);
	void flocking(Shader *shader);

};