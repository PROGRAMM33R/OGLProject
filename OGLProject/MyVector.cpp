
#include "MyVector.hpp"

void MyVector::set(float i, float o)
{
	x = i;
	y = o;
}

void MyVector::addVector(MyVector v)
{
	x += v.x;
	y += v.y;
}

// Adds to a MyVector by a constant number
void MyVector::addScalar(float s)
{
	x += s;
	y += s;
}

// Subtracts 2 vectors
void MyVector::subVector(MyVector v)
{
	x -= v.x;
	y -= v.y;
}

// Subtracts two vectors and returns the difference as a vector
MyVector MyVector::subTwoVector(MyVector v, MyVector v2)
{
	MyVector tmp;
	v.x -= v2.x;
	v.y -= v2.y;
	tmp.set(v.x, v.y);
	return tmp;
}

// Adds to a MyVector by a constant number
void MyVector::subScalar(float s)
{
	x -= s;
	y -= s;
}

// Multiplies 2 vectors
void MyVector::mulVector(MyVector v)
{
	x *= v.x;
	y *= v.y;
}

// Adds to a MyVector by a constant number
void MyVector::mulScalar(float s)
{
	x *= s;
	y *= s;
}

// Divides 2 vectors
void MyVector::divVector(MyVector v)
{
	x /= v.x;
	y /= v.y;
}

// Adds to a MyVector by a constant number
void MyVector::divScalar(float s)
{
	x /= s;
	y /= s;
}

void MyVector::limit(double max)
{
	double size = magnitude();

	if (size > max) {
		set(x / size, y / size);
	}
}

// Calculates the distance between the first MyVector and second MyVector
float MyVector::distance(MyVector v)
{
	float dx = x - v.x;
	float dy = y - v.y;
	float dist = sqrt(dx*dx + dy*dy);
	return dist;
}

// Calculates the dot product of a vector
float MyVector::dotProduct(MyVector v)
{
	float dot = x * v.x + y * v.y;
	return dot;
}

// Calculates magnitude of referenced object
float MyVector::magnitude()
{
	return sqrt(x*x + y*y);
}

void MyVector::setMagnitude(float x)
{
	normalize();
	mulScalar(x);
}

// Calculate the angle between MyVector 1 and MyVector 2
float MyVector::angleBetween(MyVector v)
{
	if (x == 0 && y == 0) return 0.0f;
	if (v.x == 0 && v.y == 0) return 0.0f;

	double dot = x * v.x + y * v.y;
	double v1mag = sqrt(x * x + y * y);
	double v2mag = sqrt(v.x * v.x + v.y * v.y);
	double amt = dot / (v1mag * v2mag); //Based of definition of dot product
										//dot product / product of magnitudes gives amt
	if (amt <= -1) {
		return PI;
	}
	else if (amt >= 1) {
		return 0;
	}
	float tmp = acos(amt);
	return tmp;
}

// normalize divides x and y by magnitude if it has a magnitude.
void MyVector::normalize()
{
	float m = magnitude();

	if (m > 0) {
		set(x / m, y / m);
	}
	else {
		set(x, y);
	}
}

// Creates and returns a copy of the MyVector used as a parameter
MyVector MyVector::copy(MyVector v)
{
	MyVector copy(v.x, v.y);
	return copy;
}