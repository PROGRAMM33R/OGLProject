#pragma once

#include "Std.hpp"
#include "MyVector.hpp"

class Boids {

private:
	int cubeSize;
	const double PI = 3.141592635;
	MyVector *oppositeVector;
	MyVector *steer, *steerMem, *sum, *desired;
	MyVector *tmpVector, *tmpVectorMem;
	MyVector *desiredAvarage;

	MyVector *separationResult;
	MyVector *aligmentResult;
	MyVector *cohesionResult;
	MyVector *wallRepelResult;

public:
	int desiredseparation, neighbordist;
	float maxSpeed, maxForce;
	bool predator;
	MyVector *location;
	MyVector *velocity;
	MyVector *acceleration;

	glm::vec3 size;

	Boids();
	~Boids();
	Boids(float x, float y, float z);
	Boids(float x, float y, float z, bool predCheck);
	
	void applyForce(MyVector *force);

	// Three Laws
	MyVector *Separation(vector<Boids*> *Boidss);
	MyVector *Alignment(vector<Boids*> *Boidss);
	MyVector *Cohesion(vector<Boids*> *Boidss);

	MyVector *WallRepel();
	MyVector *seek(MyVector *v);
	void run(vector <Boids*> *v);
	void update();
	void flock(vector <Boids*> *v);
	float angle(MyVector *v);

};