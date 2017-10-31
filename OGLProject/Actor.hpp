#pragma once

#include "Std.hpp"
#include "MyVector.hpp"

class Actor {

public:
	bool predator;
	MyVector *location;
	MyVector *velocity;
	MyVector *acceleration;
	GLfloat maxSpeed;
	GLfloat maxForce;

	glm::vec2 size;

	Actor();
	Actor(GLfloat x, GLfloat y);
	Actor(GLfloat x, GLfloat y, bool predCheck);
	
	void applyForce(MyVector *force);

	// Three Laws that boids follow
	MyVector *Separation(vector<Actor*> *Actors);
	MyVector *Alignment(vector<Actor*> *Actors);
	MyVector *Cohesion(vector<Actor*> *Actors);

	//Functions involving SFML and visualisation linking
	MyVector *seek(MyVector *v);
	void run(vector <Actor*> *v);
	void update();
	void flock(vector <Actor*> *v);
	void borders();
	GLfloat angle(MyVector *v);

private:
	const int w_height = 110;
	const int w_width = 110;
	const float PI = 3.141592635;

};