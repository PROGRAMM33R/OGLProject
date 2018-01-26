
#include "Boids.hpp"

Boids::Boids(Config *cfg, Walls *walls) {
	Boids(0.0, 0.0, 0.0, cfg, walls, false);
}

Boids::~Boids() {
	delete this->oppositeVector;
	delete this->steer;
	delete this->sum;
	delete this->desired;
	delete this->location;
	delete this->velocity;
	delete this->acceleration;
	delete this->tmpVector;
	delete this->desiredAvarage;
	delete this->origin;
	delete this->separationResult;
	delete this->aligmentResult;
	delete this->cohesionResult;
}

Boids::Boids(float x, float y, float z, Config *cfg, Walls *walls, bool predCheck = false)
{
	AxisY = 0;
	predator = predCheck;
	float angle = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * PI * 2;

	if (predCheck == true) {

		this->maxSpeed = cfg->BOID_MAX_SPEED_PREDATOR;
		this->maxForce = cfg->BOID_MAX_FORCE_PREDATOR;

		if (cfg->SCENE_TYPE == "3D") {
			velocity = new MyVector((float)this->maxSpeed, (float)(rand() % 3 - this->maxSpeed), (float)(rand() % 3 - this->maxSpeed));
		}
		else {
			velocity = new MyVector((float)this->maxSpeed, AxisY, (float)(rand() % 3 - this->maxSpeed));
		}

	}
	else {

		this->maxSpeed = cfg->BOID_MAX_SPEED;
		this->maxForce = cfg->BOID_MAX_FORCE;
		this->neighbordist = cfg->BOID_NEIGHTBORDIST;

		if (cfg->SCENE_TYPE == "3D") {
			velocity = new MyVector(cos(angle), sin(angle), tan(angle));
		}
		else {
			velocity = new MyVector(cos(angle), AxisY, tan(angle));
		}

	}

	this->desiredseparation = cfg->BOID_DESIRED_SEPARATION;
	acceleration = new MyVector();

	if (cfg->SCENE_TYPE == "3D") {
		location = new MyVector(x, y, z);
	}
	else {
		location = new MyVector(x, AxisY, z);
	}

	size.x = (float)(cfg->BOID_OBJ_SIZE);
	size.y = size.x;
	size.z = size.x;
	this->cubeSize = cfg->BOID_CUBE_SIZE / 2;
	this->steer = new MyVector();
	this->sum = new MyVector();
	this->desired = new MyVector();
	this->oppositeVector = new MyVector();
	this->tmpVector = new MyVector();
	this->desiredAvarage = new MyVector();
	this->seekResult = new MyVector();
	this->origin = new MyVector(0, 0, 0);
	this->separationResult = new MyVector();
	this->aligmentResult = new MyVector();
	this->cohesionResult = new MyVector();
	this->cfg = cfg;
	this->walls = walls;
}

inline void Boids::applyForce(MyVector *force)
{
	acceleration->addVector(force);
}

// Separation
// Keeps Boids from getting too close to one another
MyVector *Boids::Separation(vector<Boids*> *Boidss)
{
	this->steer->set();
	int count = 0;
	
	for (register int i = 0; i < Boidss->size(); i++) {
		float d = location->distance(Boidss->at(i)->location);
		if ((d > 0) && (d < this->desiredseparation) && predator == false) {
			this->tmpVector->set();
			this->tmpVectorMem = this->tmpVector;
			this->tmpVector = this->tmpVector->subTwoVector(location, Boidss->at(i)->location);
			this->tmpVector->normalize();
			this->tmpVector->divScalar(d);
			this->steer->addVector(this->tmpVector);
			delete this->tmpVector;
			this->tmpVector = this->tmpVectorMem;
			count++;
		}
		
		if ((d > 0) && (d < this->desiredseparation) && predator == true
			&& Boidss->at(i)->predator == true) {
			this->tmpVector->set();
			this->tmpVectorMem = this->tmpVector;
			this->tmpVector = this->tmpVector->subTwoVector(Boidss->at(i)->location, location);
			this->tmpVector->normalize();
			this->tmpVector->divScalar(d);
			this->steer->addVector(this->tmpVector);
			delete this->tmpVector;
			this->tmpVector = this->tmpVectorMem;
			count++;
		}
		
		else if ((d > 0) && (d < (this->desiredseparation + 300)) && Boidss->at(i)->predator == true) {
			this->tmpVector->set();
			this->tmpVectorMem = this->tmpVector;
			this->tmpVector = this->tmpVector->subTwoVector(Boidss->at(i)->location, location);
			this->tmpVector->mulScalar(900);
			this->steer->addVector(this->tmpVector);
			delete this->tmpVector;
			this->tmpVector = this->tmpVectorMem;
			count++;
		}
	}
	
	if (count > 0)
		this->steer->divScalar((float)count);
	if (this->steer->magnitude() > 0) {

		this->steer->normalize();
		this->steer->mulScalar(maxSpeed);
		this->steer->subVector(velocity);
		this->steer->limit(maxForce);

	}
	return this->steer;

}

// Alignment
// Calculates the average velocity of Boids in the field of vision and
// manipulates the velocity of the current Boids in order to match it
MyVector *Boids::Alignment(vector<Boids*> *Boidss)
{
	this->sum->set();
	this->steer->set();
	int count = 0;
	for (register int i = 0; i < Boidss->size(); i++) {
		float d = location->distance(Boidss->at(i)->location);
		if ((d > 0) && (d < this->neighbordist)) {
			this->sum->addVector(Boidss->at(i)->velocity);
			count++;
		}
	}
	
	if (count > 0) {
		this->sum->divScalar((float)count);// Divide sum by the number of close Boids (average of velocity)
		this->sum->normalize(); 
		this->sum->mulScalar(maxSpeed);
									// Steer = Desired - Velocity
		this->desiredAvarage = this->steer->subTwoVector(this->sum, velocity); //sum = desired(average)
		this->steer->set(this->desiredAvarage->vec.x, this->desiredAvarage->vec.y, this->desiredAvarage->vec.z);
		delete this->desiredAvarage;
		this->steer->limit(maxForce);
		return this->steer;
	}
	else {
		return this->sum;
	}

}

// Cohesion
// Finds the average location of nearby Boids and manipulates the
// steering force to move in that direction.
MyVector *Boids::Cohesion(vector<Boids*> *Boidss)
{
	this->sum->set();
	int count = 0;
	for (register int i = 0; i < Boidss->size(); i++) {
		float d = location->distance(Boidss->at(i)->location);
		if ((d > 0) && (d < this->neighbordist)) {
			this->sum->addVector(Boidss->at(i)->location);
			count++;
		}
	}
	if (count > 0) {
		this->sum->divScalar((float)count);
		return seek(this->sum);
	}
	else {
		return this->sum;
	}
}

// Limits the maxSpeed, finds necessary steering force and
// normalizes vectors
MyVector *Boids::seek(MyVector *v)
{
	this->desired->set();

	this->tmpVectorMem = desired->subTwoVector(v, this->location);
	this->desired->set(this->tmpVectorMem->vec.x, this->tmpVectorMem->vec.y, this->tmpVectorMem->vec.z);
	delete this->tmpVectorMem;

	this->desired->normalize();
	this->desired->mulScalar(maxSpeed);

	this->seekResult->set();
	this->tmpVectorMem = seekResult->subTwoVector(this->desired, this->velocity);
	this->seekResult->set(this->tmpVectorMem->vec.x, this->tmpVectorMem->vec.y, this->tmpVectorMem->vec.z);
	delete this->tmpVectorMem;

	seekResult->limit(maxForce);

	return this->seekResult;
}

void Boids::update()
{
	acceleration->mulScalar((float)(.4));
	velocity->addVector(acceleration);
	velocity->limit(maxSpeed);
	location->addVector(velocity);
	acceleration->mulScalar(0);
}

void Boids::run(vector <Boids*> *v)
{
	flock(v);
	update();
}

void Boids::flock(vector<Boids*> *v)
{

	this->tmpVectorMem = Separation(v);
	this->separationResult->set(
		this->tmpVectorMem->vec.x, 
		this->tmpVectorMem->vec.y, 
		this->tmpVectorMem->vec.z
	);

	this->tmpVectorMem = Alignment(v);
	this->aligmentResult->set(
		this->tmpVectorMem->vec.x, 
		this->tmpVectorMem->vec.y, 
		this->tmpVectorMem->vec.z
	);

	this->tmpVectorMem = Cohesion(v);
	this->cohesionResult->set(
		this->tmpVectorMem->vec.x, 
		this->tmpVectorMem->vec.y, 
		this->tmpVectorMem->vec.z
	);

	this->wallRepelResult = WallRepel();
	
	if (cfg->SCENE_TYPE == "3D") {
		this->separationResult->mulScalar(1.5);
		this->aligmentResult->mulScalar(1.0);
		this->cohesionResult->mulScalar(1.0);
	}
	else {
		this->separationResult->mulScalar(5.0);
		this->aligmentResult->mulScalar(1.0);
		this->cohesionResult->mulScalar(0.5);
	}
	
	applyForce(this->separationResult);
	applyForce(this->aligmentResult);
	applyForce(this->cohesionResult);
	applyForce(this->wallRepelResult);
}

MyVector *Boids::WallRepel() {
	
	this->oppositeVector->set();

	if (cfg->SCENE_TYPE == "3D") {

		if (location->distance(this->origin) > (cfg->BOID_CUBE_SIZE / 2)) {
			this->oppositeVector->addVector(location);
			this->oppositeVector->mulScalar(-.5);
			return this->oppositeVector;
		}
		else {
			this->oppositeVector->set();
			return this->oppositeVector;
		}

	}
	else {

		/*if (location->vec.x < -this->cubeSize)		location->vec.x = this->cubeSize;
		if (location->vec.x > this->cubeSize)		location->vec.x = -this->cubeSize;
		if (location->vec.z < -this->cubeSize)		location->vec.z = this->cubeSize;
		if (location->vec.z > this->cubeSize)		location->vec.z = -this->cubeSize;*/

		/*for (register int i = 0; i < this->walls->size(); i++) {

			Wall *tmpWall = this->walls->get(i);

			float xmin = tmpWall->location->vec.x;
			float xmax = tmpWall->location->vec.x + tmpWall->size->vec.x;
			float zmin = tmpWall->location->vec.z;
			float zmax = tmpWall->location->vec.z + tmpWall->size->vec.z;

			if ((location->vec.x <= xmax && location->vec.x >= xmin) && (location->vec.z <= zmax && location->vec.z >= zmin))
			{
				cout << "kolize , zed " << i << endl;
				this->oppositeVector->addVector(location);
				this->oppositeVector->mulScalar(-.5);
				return this->oppositeVector;
			}
			else {
				continue;
			}

		}*/

		//return this->oppositeVector;

		this->oppositeVector->addVector(location);
		this->oppositeVector->mulScalar(-0.5);

		if (
			location->vec.x <= -this->cubeSize ||
			location->vec.x >= this->cubeSize ||
			location->vec.y <= -this->cubeSize ||
			location->vec.y >= this->cubeSize ||
			location->vec.z <= -this->cubeSize ||
			location->vec.z >= this->cubeSize
			) {
			return this->oppositeVector;
		}
		else {
			this->oppositeVector->set();
			return this->oppositeVector;
		}
	}

}

float Boids::angle(MyVector *v) const
{
	return (float)(atan2(v->vec.x, -v->vec.y));
}

float Boids::angleX(MyVector *v) const
{
	return (float)(atan2(v->vec.y, v->vec.x));
}

float Boids::angleY(MyVector *v) const
{
	return (float)(atan2(v->vec.x, v->vec.z));
}

float Boids::angleZ(MyVector *v) const
{
	return (float)(atan2(v->vec.x, v->vec.z));
}

glm::vec3 Boids::rotationVector(MyVector *v) const {
	glm::vec3 rotation;
	float r = sqrt(pow(v->vec.x, 2) + pow(v->vec.y, 2) + pow(v->vec.z, 2));
	float theta = acos(v->vec.z / r);
	float fi = atan(v->vec.y / v->vec.x);
	rotation.x = r;
	rotation.y = theta;
	rotation.z = fi;
	return rotation;
}