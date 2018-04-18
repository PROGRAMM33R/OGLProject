#pragma once

#include <iostream>
#include "Boids.hpp"
#include "Model.hpp"
#include "InstanceStorage.hpp"

using namespace std;

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
	inline void addBoid(Boids *b);

	InstanceStorage *ISBoid;
	InstanceStorage *ISPredator;

public:
	
	Flock(Config *cfg, Walls *walls);
	~Flock() {}
	
	void flocking(Shader *shader);

};