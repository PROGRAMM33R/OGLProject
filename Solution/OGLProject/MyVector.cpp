
#include "MyVector.hpp"

MyVector::MyVector(float xComp, float yComp, float zComp) {
	vec.x = xComp; vec.y = yComp; vec.z = zComp;
}

MyVector::MyVector()
	: MyVector(0, 0, 0)
{}

void MyVector::set(float x, float y, float z)
{
	vec.x = x; vec.y = y; vec.z = z;
}

void MyVector::set(void) {
	set(0, 0, 0);
}

void MyVector::addVector(MyVector *v)
{
	vec.x += v->vec.x;
	vec.y += v->vec.y;
	vec.z += v->vec.z;
}

// Adds to a MyVector by a constant number
void MyVector::addScalar(float s)
{
	vec.x += s; vec.y += s; vec.z += s;
}

// Subtracts 2 vectors
void MyVector::subVector(MyVector *v)
{
	vec.x -= v->vec.x;
	vec.y -= v->vec.y;
	vec.z -= v->vec.z;
}

// Subtracts two vectors and returns the difference as a vector
MyVector *MyVector::subTwoVector(MyVector *v, MyVector *v2)
{
	MyVector *tmp = new MyVector();
	tmp->set(v->vec.x - v2->vec.x, v->vec.y - v2->vec.y, v->vec.z - v2->vec.z);
	return tmp;
}

// Adds to a MyVector by a constant number
void MyVector::subScalar(float s)
{
	vec.x -= s; vec.y -= s; vec.z -= s;
}

// Multiplies 2 vectors
void MyVector::mulVector(MyVector *v)
{
	vec.x *= v->vec.x;
	vec.y *= v->vec.y;
	vec.z *= v->vec.z;
}

// Adds to a MyVector by a constant number
void MyVector::mulScalar(float s)
{
	vec.x *= s; vec.y *= s; vec.z *= s;
}

// Divides 2 vectors
void MyVector::divVector(MyVector *v)
{
	vec.x /= v->vec.x;
	vec.y /= v->vec.y;
	vec.z /= v->vec.z;
}

// Adds to a MyVector by a constant number
void MyVector::divScalar(float s)
{
	vec.x /= s; vec.y /= s; vec.z /= s;
}

void MyVector::limit(float max)
{
	float size = magnitude();

	if ((int)max == 0) {
		set(0, 0, 0);
	}
	else if (size > max) {
		set(vec.x / size, vec.y / size, vec.z / size);
	}
}

// Calculates the distance between the first MyVector and second MyVector
float MyVector::distance(MyVector *v) const
{
	float dx = vec.x - v->vec.x;
	float dy = vec.y - v->vec.y;
	float dz = vec.z - v->vec.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

// Calculates the dot product of a vector
float MyVector::dotProduct(MyVector *v) const
{
	return vec.x * v->vec.x + vec.y * v->vec.y + vec.z * v->vec.z;
}

// Calculates magnitude of referenced object
float MyVector::magnitude() const
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

void MyVector::setMagnitude(float x)
{
	normalize();
	mulScalar(x);
}

// Calculate the angle between MyVector 1 and MyVector 2
float MyVector::angleBetween(MyVector *v)
{
	MyVector *v1 = v;
	MyVector *v2 = this;
	float result = 0.0;
	v1->normalize();
	v2->normalize();
	if ((v1->vec.x == v2->vec.x) && (v1->vec.y == v2->vec.y) && (v1->vec.z == v2->vec.z)){
		return 0;
	}
	else{
		return acos(v1->dotProduct(v2));
	}
}

void MyVector::normalize(void)
{
	float len = magnitude();
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
}

MyVector *MyVector::copy(MyVector v) const
{
	return new MyVector(v.vec.x, v.vec.y, v.vec.z);
}