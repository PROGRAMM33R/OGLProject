#pragma once

#include <cmath>

class MyVector {

private:
	struct vec3 {
		float x, y, z;
	};
	const double PI = 3.141592654;

public:
	vec3 vec;	

	MyVector();

	MyVector(float xComp, float yComp, float zComp);

	void set(float x, float y, float z);
	void set(void);

	virtual void addVector(MyVector *v);
	virtual void addScalar(float x);

	virtual void subVector(MyVector *v);
	virtual MyVector *subTwoVector(MyVector *v, MyVector *v2);
	virtual void subScalar(float x);

	virtual void mulVector(MyVector *v);
	virtual void mulScalar(float x);

	virtual void divVector(MyVector *v);
	virtual void divScalar(float x);

	virtual void limit(float max);

	virtual float distance(MyVector *v) const;
	virtual float dotProduct(MyVector *v) const;
	virtual float magnitude() const;
	virtual void setMagnitude(float x);
	virtual float angleBetween(MyVector *v);
	virtual void normalize(void);

	MyVector *copy(MyVector v) const;

};