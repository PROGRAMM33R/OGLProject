#pragma once

#include "Std.hpp"

class MyVector {

public:
	glm::vec2 vec;

	MyVector() {}

	MyVector(GLfloat xComp, GLfloat yComp)
	{
		vec.x = xComp; vec.y = yComp;
	}

	//Mutator Functions
	void set(GLfloat x, GLfloat y);

	//Scalar functions scale a vector by a float
	void addVector(MyVector *v);
	void addScalar(GLfloat x);

	void subVector(MyVector *v);
	MyVector *subTwoVector(MyVector *v, MyVector *v2);
	void subScalar(GLfloat x);

	void mulVector(MyVector *v);
	void mulScalar(GLfloat x);

	void divVector(MyVector *v);
	void divScalar(GLfloat x);

	void limit(GLfloat max);

	//Calculating Functions
	GLfloat distance(MyVector *v);
	GLfloat dotProduct(MyVector *v);
	GLfloat magnitude();
	void setMagnitude(GLfloat x);
	GLfloat angleBetween(MyVector *v);
	void normalize();

	MyVector *copy(MyVector v);

private:
	const float PI = 3.141592654;

};