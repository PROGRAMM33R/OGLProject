
#include "Actor.hpp"

Actor::Actor(GLfloat x, GLfloat y)
{
	acceleration = new MyVector(0, 0);
	velocity = new MyVector(rand() % 10 / 1000.0, rand() % 10 / 1000.0);
	location = new MyVector(x, y);
	maxSpeed = 0.005;
	maxForce = 1;
	size.x = 1;
	size.y = 1;
}

Actor::Actor() {
	Actor(0.0, 0.0);
}

Actor::Actor(GLfloat x, GLfloat y, bool predCheck)
{
	predator = predCheck;
	if (predCheck == true) {
		maxSpeed = 0.008;
		maxForce = 0.009;
		velocity = new MyVector(rand() % 10 / 1000.0, rand() % 10 / 1000.0);
	}
	else {
		maxSpeed = 0.005;
		maxForce = 0.006;
		velocity = new MyVector(rand() % 10 / 1000.0, rand() % 10 / 1000.0);
	}
	acceleration = new MyVector(0, 0);
	location = new MyVector(x, y);
	size.x = 1;
	size.y = 1;
}

// Adds force MyVector to current force MyVector
void Actor::applyForce(MyVector *force)
{
	acceleration->addVector(force);
}

// Separation
// Keeps Actors from getting too close to one another
MyVector *Actor::Separation(vector<Actor*> *Actors)
{
	// Distance of field of vision for separation between Actors
	float desiredseparation = 20;
	MyVector *steer = new MyVector(0, 0);
	int count = 0;
	// For every Actor in the system, check if it's too close
	for (int i = 0; i < Actors->size(); i++) {
		// Calculate distance from current Actor to Actor we're looking at
		float d = location->distance(Actors->at(i)->location);
		// If this is a fellow Actor and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation)) {
			MyVector *diff = new MyVector(0, 0);
			diff = diff->subTwoVector(location, Actors->at(i)->location);
			diff->normalize();
			diff->divScalar(d);      // Weight by distance
			steer->addVector(diff);
			count++;
		}
		// If current Actor is a predator and the Actor we're looking at is also
		// a predator, then separate only slightly
		if ((d > 0) && (d < desiredseparation) && predator == true
			&& Actors->at(i)->predator == true) {
			MyVector *pred2pred = new MyVector(0, 0);
			pred2pred = pred2pred->subTwoVector(location, Actors->at(i)->location);
			pred2pred->normalize();
			pred2pred->divScalar(d);
			steer->addVector(pred2pred);
			count++;
		}
		// If current Actor is not a predator, but the Actor we're looking at is
		// a predator, then create a large separation MyVector
		else if ((d > 0) && (d < desiredseparation + 70) && Actors->at(i)->predator == true) {
			MyVector *pred = new MyVector(0, 0);
			pred = pred->subTwoVector(location, Actors->at(i)->location);
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
// Calculates the average velocity of Actors in the field of vision and
// manipulates the velocity of the current Actor in order to match it
MyVector *Actor::Alignment(vector<Actor*> *Actors)
{
	float neighbordist = 50; // Field of vision

	MyVector *sum = new MyVector(0, 0);
	int count = 0;
	for (int i = 0; i < Actors->size(); i++) {
		float d = location->distance(Actors->at(i)->location);
		if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
			sum->addVector(Actors->at(i)->velocity);
			count++;
		}
	}
	// If there are Actors close enough for alignment...
	if (count > 0) {
		sum->divScalar((float)count);// Divide sum by the number of close Actors (average of velocity)
		sum->normalize();            // Turn sum into a unit vector, and
		sum->mulScalar(maxSpeed);    // Multiply by maxSpeed
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
// Finds the average location of nearby Actors and manipulates the
// steering force to move in that direction.
MyVector *Actor::Cohesion(vector<Actor*> *Actors)
{
	float neighbordist = 50;
	MyVector *sum = new MyVector(0, 0);
	int count = 0;
	for (int i = 0; i < Actors->size(); i++) {
		float d = location->distance(Actors->at(i)->location);
		if ((d > 0) && (d < neighbordist)) {
			sum->addVector(Actors->at(i)->location);
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
MyVector *Actor::seek(MyVector *v)
{
	MyVector *desired = new MyVector();
	desired->subVector(v);  // A vector pointing from the location to the target
						   // Normalize desired and scale to maximum speed
	desired->normalize();
	desired->mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration->subTwoVector(desired, velocity);
	acceleration->limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

// Modifies velocity, location, and resets acceleration with values that
// are given by the three laws.
void Actor::update()
{
	//To make the slow down not as abrupt
	acceleration->mulScalar(.4);
	// Update velocity
	velocity->addVector(acceleration);
	// Limit speed
	velocity->limit(maxSpeed);
	location->addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration->mulScalar(0);
}

// Run flock() on the flock of Actors.
// This applies the three rules, modifies velocities accordingly, updates data,
// and corrects Actors which are sitting outside of the SFML window
void Actor::run(vector <Actor*> *v)
{
	flock(v);
	update();
	borders();
}

// Applies the three laws to the flock of Actors
void Actor::flock(vector<Actor*> *v)
{
	MyVector *sep = Separation(v);
	MyVector *ali = Alignment(v);
	MyVector *coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep->mulScalar(1.5);
	ali->mulScalar(1.0); // Might need to alter weights for different characteristics
	coh->mulScalar(1.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

// Checks if Actors go out of the window and if so, wraps them around to
// the other side.
void Actor::borders()
{
	int widthHalf = w_width / 2;
	int heightHalf = w_height / 2;
	if (location->vec.x < -widthHalf)    location->vec.x += w_width;
	if (location->vec.y < -heightHalf)   location->vec.y += w_height;
	if (location->vec.x > widthHalf)     location->vec.x -= w_width;
	if (location->vec.y > heightHalf)    location->vec.y -= w_height;
}

// Calculates the angle for the velocity of a Actor which allows the visual
// image to rotate in the direction that it is going in.
float Actor::angle(MyVector *v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v->vec.x, -v->vec.y) * 180 / PI);
	return angle;
}