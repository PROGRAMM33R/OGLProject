#pragma once

#include "Std.hpp"
#include "MyVector.hpp"
#include "Walls.hpp"

class Boids {

private:
	Config *cfg;
	Walls *walls;
	int cubeSize;
	const double PI = 3.141592635;
	float AxisY;
	MyVector *oppositeVector;
	MyVector *steer, *steerMem, *sum, *desired;
	MyVector *tmpVector, *tmpVectorMem;
	MyVector *desiredAvarage, *origin, *seekResult;

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

	Boids(Config *cfg, Walls *walls);
	~Boids();
	Boids(float x, float y, float z, Config *cfg, Walls *walls, bool predCheck);
	
	inline void applyForce(MyVector *force);

	// Three Laws
	MyVector *Separation(vector<Boids*> *Boidss);
	MyVector *Alignment(vector<Boids*> *Boidss);
	MyVector *Cohesion(vector<Boids*> *Boidss);

	MyVector *WallRepel();
	MyVector *seek(MyVector *v);
	void run(vector <Boids*> *v);
	void update();
	void flock(vector <Boids*> *v);
	float angle(MyVector *v) const;
	float angleX(MyVector *v) const;
	float angleY(MyVector *v) const;
	float angleZ(MyVector *v) const;
	glm::vec3 rotationVector(MyVector *v) const;

};