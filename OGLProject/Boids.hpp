#pragma once

#include "Std.hpp"
#include "MyVector.hpp"

class Boids {

public:
	bool predator;
	MyVector *location;
	MyVector *velocity;
	MyVector *acceleration;
	GLfloat maxSpeed;
	GLfloat maxForce;

	glm::vec2 size;

	Boids();
	Boids(GLfloat x, GLfloat y);
	Boids(GLfloat x, GLfloat y, bool predCheck);
	
	void applyForce(MyVector *force);

	// Three Laws that boids follow
	MyVector *Separation(vector<Boids*> *Boidss);
	MyVector *Alignment(vector<Boids*> *Boidss);
	MyVector *Cohesion(vector<Boids*> *Boidss);

	//Functions involving SFML and visualisation linking
	MyVector *seek(MyVector *v);
	void run(vector <Boids*> *v);
	void update();
	void flock(vector <Boids*> *v);
	void borders();
	GLfloat angle(MyVector *v);

private:
	const int w_height = 4100;
	const int w_width = 4100;
	const float PI = 3.141592635;

};