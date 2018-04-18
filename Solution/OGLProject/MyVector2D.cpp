
#include "MyVector2D.hpp"

MyVector2D::MyVector2D(float xComp, float yComp, float zComp)
	:MyVector(xComp, yComp, zComp)
{}

MyVector2D::MyVector2D()
	: MyVector2D(0, 0, 0)
{}

void MyVector2D::addVector(MyVector *v)
{
	vec.x += v->vec.x;
	vec.z += v->vec.z;
}

// Adds to a MyVector2D by a constant number
void MyVector2D::addScalar(float s)
{
	vec.x += s; vec.z += s;
}

// Subtracts 2 vectors
void MyVector2D::subVector(MyVector *v)
{
	vec.x -= v->vec.x;
	vec.z -= v->vec.z;
}

// Subtracts two vectors and returns the difference as a vector
MyVector *MyVector2D::subTwoVector(MyVector *v, MyVector *v2)
{
	MyVector *tmp = new MyVector();
	tmp->set(v->vec.x - v2->vec.x, v->vec.y, v->vec.z - v2->vec.z);
	return tmp;
}

// Adds to a MyVector2D by a constant number
void MyVector2D::subScalar(float s)
{
	vec.x -= s; vec.z -= s;
}

// Multiplies 2 vectors
void MyVector2D::mulVector(MyVector *v)
{
	vec.x *= v->vec.x;
	vec.z *= v->vec.z;
}

// Adds to a MyVector2D by a constant number
void MyVector2D::mulScalar(float s)
{
	vec.x *= s; vec.z *= s;
}

// Divides 2 vectors
void MyVector2D::divVector(MyVector *v)
{
	vec.x /= v->vec.x;
	vec.z /= v->vec.z;
}

// Adds to a MyVector2D by a constant number
void MyVector2D::divScalar(float s)
{
	vec.x /= s; vec.z /= s;
}

void MyVector2D::limit(float max)
{
	float size = magnitude();

	if (size > max) {
		set(vec.x / size, vec.y, vec.z / size);
	}
}

// Calculates the distance between the first MyVector2D and second MyVector2D
float MyVector2D::distance(MyVector *v) const
{
	float dx = vec.x - v->vec.x;
	float dz = vec.z - v->vec.z;
	return sqrt(dx*dx + dz * dz);
}

// Calculates the dot product of a vector
float MyVector2D::dotProduct(MyVector *v) const
{
	return vec.x * v->vec.x + vec.z * v->vec.z;
}

// Calculates magnitude of referenced object
float MyVector2D::magnitude() const
{
	return sqrt(vec.x*vec.x + vec.z*vec.z);
}

void MyVector2D::setMagnitude(float x)
{
	normalize();
	mulScalar(x);
}

// Calculate the angle between MyVector2D 1 and MyVector2D 2
float MyVector2D::angleBetween(MyVector *v)
{
	MyVector *v1 = v;
	MyVector *v2 = this;
	float result = 0.0;
	v1->normalize();
	v2->normalize();
	if ((v1->vec.x == v2->vec.x) && (v1->vec.y == v2->vec.y) && (v1->vec.z == v2->vec.z)) {
		return 0;
	}
	else {
		return acos(v1->dotProduct(v2));
	}
}

void MyVector2D::normalize(void)
{
	float len = magnitude();
	vec.x /= len;
	vec.z /= len;
}