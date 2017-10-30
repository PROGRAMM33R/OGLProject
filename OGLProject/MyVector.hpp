#pragma once

#include "Std.hpp"

class MyVector {

public:
	float x;
	float y;

	MyVector() {}

	MyVector(float xComp, float yComp)
	{
		x = xComp;
		y = yComp;
	}

	//Mutator Functions
	void set(float x, float y);

	//Scalar functions scale a vector by a float
	void addVector(MyVector v);
	void addScalar(float x);

	void subVector(MyVector v);
	MyVector subTwoVector(MyVector v, MyVector v2);
	void subScalar(float x);

	void mulVector(MyVector v);
	void mulScalar(float x);

	void divVector(MyVector v);
	void divScalar(float x);

	void limit(double max);

	//Calculating Functions
	float distance(MyVector v);
	float dotProduct(MyVector v);
	float magnitude();
	void setMagnitude(float x);
	float angleBetween(MyVector v);
	void normalize();

	MyVector copy(MyVector v);

private:
	const float PI = 3.141592654;

};