
#include "MyVector.hpp"

void MyVector::set(GLfloat i, GLfloat o)
{
	vec.x = i; vec.y = o;
}

void MyVector::addVector(MyVector *v)
{
	vec.x += v->vec.x;
	vec.y += v->vec.y;
}

// Adds to a MyVector by a constant number
void MyVector::addScalar(GLfloat s)
{
	vec.x += s; vec.y += s;
}

// Subtracts 2 vectors
void MyVector::subVector(MyVector *v)
{
	vec.x -= v->vec.x;
	vec.y -= v->vec.y;
}

// Subtracts two vectors and returns the difference as a vector
MyVector *MyVector::subTwoVector(MyVector *v, MyVector *v2)
{
	MyVector *tmp = new MyVector();
	v->vec.x -= v2->vec.x;
	v->vec.y -= v2->vec.y;
	tmp->set(v->vec.x, v->vec.y);
	return tmp;
}

// Adds to a MyVector by a constant number
void MyVector::subScalar(GLfloat s)
{
	vec.x -= s; vec.y -= s;
}

// Multiplies 2 vectors
void MyVector::mulVector(MyVector *v)
{
	vec.x *= v->vec.x;
	vec.y *= v->vec.y;
}

// Adds to a MyVector by a constant number
void MyVector::mulScalar(GLfloat s)
{
	vec.x *= s; vec.y *= s;
}

// Divides 2 vectors
void MyVector::divVector(MyVector *v)
{
	vec.x /= v->vec.x;
	vec.y /= v->vec.y;
}

// Adds to a MyVector by a constant number
void MyVector::divScalar(GLfloat s)
{
	vec.x /= s; vec.y /= s;
}

void MyVector::limit(GLfloat max)
{
	GLfloat size = magnitude();

	if (size > max) {
		set(vec.x / size, vec.y / size);
	}
}

// Calculates the distance between the first MyVector and second MyVector
GLfloat MyVector::distance(MyVector *v)
{
	GLfloat dx = vec.x - v->vec.x;
	GLfloat dy = vec.y - v->vec.y;
	GLfloat dist = sqrt(dx*dx + dy*dy);
	return dist;
}

// Calculates the dot product of a vector
GLfloat MyVector::dotProduct(MyVector *v)
{
	GLfloat dot = vec.x * v->vec.x + vec.y * v->vec.y;
	return dot;
}

// Calculates magnitude of referenced object
GLfloat MyVector::magnitude()
{
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

void MyVector::setMagnitude(GLfloat x)
{
	normalize();
	mulScalar(x);
}

// Calculate the angle between MyVector 1 and MyVector 2
GLfloat MyVector::angleBetween(MyVector *v)
{
	if (vec.x == 0 && vec.y == 0) return 0.0f;
	if (v->vec.x == 0 && v->vec.y == 0) return 0.0f;

	double dot = vec.x * v->vec.x + vec.y * v->vec.y;
	double v1mag = sqrt(vec.x * vec.x + vec.y * vec.y);
	double v2mag = sqrt(v->vec.x * v->vec.x + v->vec.y * v->vec.y);
	double amt = dot / (v1mag * v2mag); //Based of definition of dot product
										//dot product / product of magnitudes gives amt
	if (amt <= -1) {
		return PI;
	}
	else if (amt >= 1) {
		return 0;
	}
	GLfloat tmp = acos(amt);
	return tmp;
}

// normalize divides x and y by magnitude if it has a magnitude.
void MyVector::normalize()
{
	GLfloat m = magnitude();

	if (m > 0) {
		set(vec.x / m, vec.y / m);
	}
	else {
		set(vec.x, vec.y);
	}
}

// Creates and returns a copy of the MyVector used as a parameter
MyVector *MyVector::copy(MyVector v)
{
	MyVector *copy = new MyVector(v.vec.x, v.vec.y);
	return copy;
}