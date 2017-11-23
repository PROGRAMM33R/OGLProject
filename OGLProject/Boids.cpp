
#include "Boids.hpp"

Boids::Boids(GLfloat x, GLfloat y)
{
	acceleration = new MyVector(0, 0);
	velocity = new MyVector(rand() % 3 - 2, rand() % 3 - 2);
	location = new MyVector(x, y);
	maxSpeed = 0.5;
	maxForce = 0.3;
	size.x = 7;
	size.y = 7;
}

Boids::Boids() {
	Boids(0.0, 0.0);
}

Boids::Boids(GLfloat x, GLfloat y, bool predCheck)
{
	predator = predCheck;
	if (predCheck == true) {
		maxSpeed = 3.0;
		maxForce = 0.3;
		velocity = new MyVector(rand() % 3 - 1, rand() % 3 - 1);
	}
	else {
		maxSpeed = 0.5;
		maxForce = 0.3;
		velocity = new MyVector(rand() % 3 - 2, rand() % 3 - 2);
	}
	acceleration = new MyVector(0, 0);
	location = new MyVector(x, y);
	size.x = 7;
	size.y = 7;
}

void Boids::applyForce(MyVector *force)
{
	acceleration->addVector(force);
}

// Separation
// Keeps Boidss from getting too close to one another
MyVector *Boids::Separation(vector<Boids*> *Boidss)
{
	float desiredseparation = 100;
	MyVector *steer = new MyVector(0, 0);
	int count = 0;
	
	for (int i = 0; i < Boidss->size(); i++) {
		float d = location->distance(Boidss->at(i)->location);
		if ((d > 0) && (d < desiredseparation)) {
			MyVector *diff = new MyVector(0, 0);
			diff = diff->subTwoVector(location, Boidss->at(i)->location);
			diff->normalize();
			diff->divScalar(d); 
			steer->addVector(diff);
			count++;
		}
		// If current Boids is a predator and the Boids we're looking at is also
		// a predator, then separate only slightly
		if ((d > 0) && (d < desiredseparation) && predator == true
			&& Boidss->at(i)->predator == true) {
			MyVector *pred2pred = new MyVector(0, 0);
			pred2pred = pred2pred->subTwoVector(location, Boidss->at(i)->location);
			pred2pred->normalize();
			pred2pred->divScalar(d);
			steer->addVector(pred2pred);
			count++;
		}
		// If current Boids is not a predator, but the Boids we're looking at is
		// a predator, then create a large separation MyVector
		else if ((d > 0) && (d < desiredseparation + 150) && Boidss->at(i)->predator == true) {
			MyVector *pred = new MyVector(0, 0);
			pred = pred->subTwoVector(location, Boidss->at(i)->location);
			pred->mulScalar(900);
			steer->addVector(pred);
			count++;
		}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer->divScalar((float)count);
	if (steer->magnitude() > 0) {
		// Steering = Desired - Velocity
		steer->normalize();
		steer->mulScalar(maxSpeed);
		steer->subVector(velocity);
		steer->limit(maxForce);
	}
	return steer;
}

// Alignment
// Calculates the average velocity of Boidss in the field of vision and
// manipulates the velocity of the current Boids in order to match it
MyVector *Boids::Alignment(vector<Boids*> *Boidss)
{
	float neighbordist = 130;

	MyVector *sum = new MyVector(0, 0);
	int count = 0;
	for (int i = 0; i < Boidss->size(); i++) {
		float d = location->distance(Boidss->at(i)->location);
		if ((d > 0) && (d < neighbordist)) {
			sum->addVector(Boidss->at(i)->velocity);
			count++;
		}
	}
	// If there are Boidss close enough for alignment...
	if (count > 0) {
		sum->divScalar((float)count);// Divide sum by the number of close Boidss (average of velocity)
		sum->normalize();            // Turn sum into a unit vector, and
		sum->mulScalar(maxSpeed);  
									// Steer = Desired - Velocity
		MyVector *steer = new MyVector();
		steer = steer->subTwoVector(sum, velocity); //sum = desired(average)
		steer->limit(maxForce);
		return steer;
	}
	else {
		MyVector *temp = new MyVector(0, 0);
		return temp;
	}
}

// Cohesion
// Finds the average location of nearby Boidss and manipulates the
// steering force to move in that direction.
MyVector *Boids::Cohesion(vector<Boids*> *Boidss)
{
	float neighbordist = 130;
	MyVector *sum = new MyVector(0, 0);
	int count = 0;
	for (int i = 0; i < Boidss->size(); i++) {
		float d = location->distance(Boidss->at(i)->location);
		if ((d > 0) && (d < neighbordist)) {
			sum->addVector(Boidss->at(i)->location);
			count++;
		}
	}
	if (count > 0) {
		sum->divScalar(count);
		return seek(sum);
	}
	else {
		MyVector *temp = new MyVector(0, 0);
		return temp;
	}
}

// Limits the maxSpeed, finds necessary steering force and
// normalizes vectors
MyVector *Boids::seek(MyVector *v)
{
	MyVector *desired = new MyVector();
	desired->subVector(v);  // A vector pointing from the location to the target
						   // Normalize desired and scale to maximum speed
	desired->normalize();
	desired->mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration->subTwoVector(desired, velocity);
	acceleration->limit(maxForce); 
	return acceleration;
}

void Boids::update()
{
	acceleration->mulScalar(.4);
	velocity->addVector(acceleration);
	velocity->limit(maxSpeed);
	location->addVector(velocity);
	acceleration->mulScalar(0);
}

void Boids::run(vector <Boids*> *v)
{
	flock(v);
	update();
	borders();
}

void Boids::flock(vector<Boids*> *v)
{
	MyVector *sep = Separation(v);
	MyVector *ali = Alignment(v);
	MyVector *coh = Cohesion(v);
	
	sep->mulScalar(0.5);
	ali->mulScalar(0.1);
	coh->mulScalar(0.1);
	
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

void Boids::borders()
{
	int widthHalf = w_width / 2;
	int heightHalf = w_height / 2;
	if (location->vec.x < -widthHalf)    location->vec.x += w_width;
	if (location->vec.y < -heightHalf)   location->vec.y += w_height;
	if (location->vec.x > widthHalf)     location->vec.x -= w_width;
	if (location->vec.y > heightHalf)    location->vec.y -= w_height;
}

float Boids::angle(MyVector *v)
{
	float angle = (float)(atan2(v->vec.x, -v->vec.y) * 180 / PI);
	return angle;
}