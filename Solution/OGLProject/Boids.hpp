#pragma once

#include <iostream>
#include <cmath>
#include "MyVector.hpp"
#include "MyVector2D.hpp"
#include "Walls.hpp"

using namespace std;

class Boids {

private:
	Config *cfg;
	Walls *walls;
	int cubeSize;
	const double PI = 3.141592635;
	float AxisY;
	float minDistance = 0, minIndex = 1;
	bool getArriveVectorFirstTime = false;
	bool incrementedOnce = false;
	int floor;
	std::clock_t start;
	double escapeDuration;
	bool startMovingToNextFloor = false;
	int alignmentSensitivity = 1.0;

	MyVector *oppositeVector;
	MyVector *steer, *steerMem, *sum, *desired;
	MyVector *tmpVector, *tmpVectorMem;
	MyVector *desiredAvarage, *origin, *seekResult;

	MyVector *separationResult;
	MyVector *aligmentResult;
	MyVector *cohesionResult;
	MyVector *wallRepelResult;
	MyVector *arriveToResult;

	vector<int> *finishedPoints;

	// Three Laws
	MyVector *Separation(vector<Boids*> *Boidss);
	MyVector *Alignment(vector<Boids*> *Boidss);
	MyVector *Cohesion(vector<Boids*> *Boidss);

	MyVector *WallRepel();
	MyVector *seek(MyVector *v);

	MyVector *arriveTo(MyVector *v);
	MyVector *getArriveVector(void);

	inline void applyForce(MyVector *force);

	MyVector *WallCollision(float direction, MyVector *_desired);

	void update();

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
	Boids(MyVector *newLocation, Config *cfg, Walls *walls, bool predCheck, int floor);

	void run(vector <Boids*> *v);
	void flock(vector <Boids*> *v);

	float angle(MyVector *v) const;
	float angleX(MyVector *v) const;
	float angleY(MyVector *v) const;
	float angleZ(MyVector *v) const;

	float angleR(MyVector *v) const;
	float angleFi(MyVector *v) const;
	float angleTheta(MyVector *v) const;

};