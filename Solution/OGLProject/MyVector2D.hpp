#pragma once

#include <cmath>
#include "MyVector.hpp"

class MyVector2D final : public MyVector {

public:
	MyVector2D();

	MyVector2D(float xComp, float yComp, float zComp);

	void addVector(MyVector *v) final;
	void addScalar(float x) final;

	void subVector(MyVector *v) final;
	MyVector *subTwoVector(MyVector *v, MyVector *v2) final;
	void subScalar(float x) final;

	void mulVector(MyVector *v) final;
	void mulScalar(float x) final;

	void divVector(MyVector *v) final;
	void divScalar(float x) final;

	void limit(float max) final;

	float distance(MyVector *v) const final;
	float dotProduct(MyVector *v) const final;
	float magnitude() const final;
	void setMagnitude(float x) final;
	float angleBetween(MyVector *v) final;
	void normalize(void) final;

};