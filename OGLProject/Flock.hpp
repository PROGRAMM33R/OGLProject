#pragma once

#include "Std.hpp"
#include "Boids.hpp"
#include "Model.hpp"

class Shader;
class Walls;
class Flock {

private:
	int numberOfBoids, numberOfPredators;
	vector<Boids*> *flock;
	Model **boidsModel;
	Config *cfg;
	Walls *walls;

	void loadModels(void);

public:
	
	Flock(int numberOfBoids, int numberOfPredators, int initialSpacingBetweenBoids, Config *cfg, Walls *walls);
	Flock(Config *cfg, Walls *walls);
	~Flock() {}
	
	void addBoid(Boids *b);
	void flocking(Shader *shader);

};