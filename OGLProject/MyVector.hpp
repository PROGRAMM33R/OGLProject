#pragma once

#include "Std.hpp"

class MyVector {

public:
	glm::vec3 vec;

	MyVector();

	MyVector(float xComp, float yComp, float zComp);

	void set(float x, float y, float z);
	void set(void);

	void addVector(MyVector *v);
	void addScalar(float x);

	void subVector(MyVector *v);
	MyVector *subTwoVector(MyVector *v, MyVector *v2);
	void subScalar(float x);

	void mulVector(MyVector *v);
	void mulScalar(float x);

	void divVector(MyVector *v);
	void divScalar(float x);

	void limit(float max);

	float distance(MyVector *v) const;
	float dotProduct(MyVector *v) const;
	float magnitude() const;
	void setMagnitude(float x);
	float angleBetween(MyVector *v);
	void normalize(void);

	MyVector *copy(MyVector v) const;

private:
	const double PI = 3.141592654;

};