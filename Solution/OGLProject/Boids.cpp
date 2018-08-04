
#include "Boids.hpp"

Boids::Boids(Config *cfg, Walls *walls) {
	Boids(new MyVector(0, 0, 0), cfg, walls, false, 0);
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
	delete this->wallRepelResult;
	delete this->arriveToResult;
	delete this->finishedPoints;
}

Boids::Boids(MyVector *newLocation, Config *cfg, Walls *walls, bool predCheck = false, int floor = 0)
{
	AxisY = 1000;
	predator = predCheck;
	this->floor = floor;
	float angle = (float)(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * PI * 2;

	if (this->predator) {

		this->maxSpeed = cfg->BOID_MAX_SPEED_PREDATOR;
		this->maxForce = cfg->BOID_MAX_FORCE_PREDATOR;

		if (cfg->SCENE_TYPE == "3D") {
			velocity = new MyVector((float)this->maxSpeed, (float)(rand() % 3 - this->maxSpeed), (float)(rand() % 3 - this->maxSpeed));
		}
		else {
			velocity = new MyVector2D((float)this->maxSpeed, AxisY, (float)(rand() % 3 - this->maxSpeed));
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
			velocity = new MyVector2D(cos(angle), AxisY, tan(angle));
		}

	}

	this->desiredseparation = cfg->BOID_DESIRED_SEPARATION;

	if (cfg->SCENE_TYPE == "3D") {
		location = new MyVector(newLocation->vec.x, newLocation->vec.y, newLocation->vec.z);
		acceleration = new MyVector();

		if (this->predator) {
			size.x = (float)(cfg->BOID_PREDATOR_SIZE);
			size.y = size.x;
			size.z = size.x;
		}
		else {
			size.x = (float)(cfg->BOID_OBJ_SIZE);
			size.y = size.x;
			size.z = size.x;
		}
		
	}
	else {
		location = new MyVector2D(newLocation->vec.x, newLocation->vec.y, newLocation->vec.z);
		acceleration = new MyVector2D();
		size.x = (float)(cfg->BOID_OBJ_SIZE);
		size.y = size.x;
		size.z = size.x;
	}

	
	this->cubeSize = cfg->BOID_CUBE_SIZE / 2;

	if (cfg->SCENE_TYPE == "3D") {
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
		this->wallRepelResult = new MyVector();
		this->arriveToResult = new MyVector();
		
	}
	else {
		this->steer = new MyVector2D();
		this->sum = new MyVector2D();
		this->desired = new MyVector2D();
		this->oppositeVector = new MyVector2D();
		this->tmpVector = new MyVector2D();
		this->desiredAvarage = new MyVector2D();
		this->seekResult = new MyVector2D();
		this->origin = new MyVector2D(0, 0, 0);
		this->separationResult = new MyVector2D();
		this->aligmentResult = new MyVector2D();
		this->cohesionResult = new MyVector2D();
		this->wallRepelResult = new MyVector2D();
		this->arriveToResult = new MyVector2D();
	}
	
	this->finishedPoints = new vector<int>();
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
	
	for (int i = 0, len = Boidss->size(); i < len; ++i) {
		if (Boidss->at(i)->floor == this->floor) {
			float d = location->distance(Boidss->at(i)->location);
			if ((d > 0) && (d < this->desiredseparation) /*&& predator == false*/) {
				this->tmpVector->set();
				this->tmpVectorMem = this->tmpVector;
				this->tmpVector = this->tmpVector->subTwoVector(location, Boidss->at(i)->location);
				this->tmpVector->normalize();
				this->tmpVector->divScalar(d);
				this->steer->addVector(this->tmpVector);
				delete this->tmpVector;
				this->tmpVector = this->tmpVectorMem;
				++count;
			}

			if (this->predator) {
				if ((d > 0) && (d < this->desiredseparation + (this->desiredseparation + this->cfg->BOID_PREDATOR_SIZE * 13))) {
					this->tmpVector->set();
					this->tmpVectorMem = this->tmpVector;
					this->tmpVector = this->tmpVector->subTwoVector(location, Boidss->at(i)->location);
					this->tmpVector->normalize();
					this->tmpVector->divScalar(d);
					this->steer->addVector(this->tmpVector);
					delete this->tmpVector;
					this->tmpVector = this->tmpVectorMem;
					++count;
				}
			}

			if ((d > 0) && (this->desiredseparation + (this->desiredseparation + this->cfg->BOID_PREDATOR_SIZE * 10)) && predator == true
				&& Boidss->at(i)->predator == true) {
				this->tmpVector->set();
				this->tmpVectorMem = this->tmpVector;
				this->tmpVector = this->tmpVector->subTwoVector(location, Boidss->at(i)->location);
				this->tmpVector->normalize();
				this->tmpVector->divScalar(d);
				this->steer->addVector(this->tmpVector);
				delete this->tmpVector;
				this->tmpVector = this->tmpVectorMem;
				++count;
			}
			else if ((d > 0) && (d < (this->desiredseparation + this->cfg->BOID_PREDATOR_SIZE * 12)) && Boidss->at(i)->predator == true) {
				this->tmpVector->set();
				this->tmpVectorMem = this->tmpVector;
				this->tmpVector = this->tmpVector->subTwoVector(location, Boidss->at(i)->location);
				this->tmpVector->mulScalar(900);
				this->steer->addVector(this->tmpVector);
				delete this->tmpVector;
				this->tmpVector = this->tmpVectorMem;
				++count;
			}
			
		}
	}
	
	if (this->steer->magnitude() > 0 ) {

		this->steer->divScalar((float)count);
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
	for (int i = 0, len = Boidss->size(); i < len; ++i) {
		if (Boidss->at(i)->floor == this->floor) {
			float d = location->distance(Boidss->at(i)->location);
			if ((d > 0) && (d < this->neighbordist)) {
				this->sum->addVector(Boidss->at(i)->velocity);
				++count;
			}
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
	for (int i = 0, len = Boidss->size(); i < len; ++i) {
		if (Boidss->at(i)->floor == this->floor) {
			float d = location->distance(Boidss->at(i)->location);
			if ((d > 0) && (d < this->neighbordist)) {
				this->sum->addVector(Boidss->at(i)->location);
				++count;
			}
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

MyVector *Boids::arriveTo(MyVector *v) {
	return seek(v);
}

MyVector *Boids::getArriveVector(void) {

	if (!this->getArriveVectorFirstTime && !walls->labyrint) {

		int floorIndex = 1;
		
		for (int i = 1, len = walls->exitPositions.size(); i <= len; ++i) {

			if (walls->exitPositions.at(i) != NULL) {
				if ((walls->exitPositions.at(i)->vec.y / walls->floorDiferencial) == this->floor) {
					floorIndex = i;
					break;
				}
			}
			
		}
		
		for (int i = 0, j = floorIndex; j < 24; ++i, j += 2) { // 24 for whole EN alphabet
			if (walls->exitPositions[j] != NULL) {

				if ((walls->exitPositions.at(j)->vec.y / walls->floorDiferencial) == this->floor) {
					float d = location->distance(walls->exitPositions[j]);

					if (i == 0) {
						this->minDistance = d;
						this->minIndex = j;
					}
					else if (d < this->minDistance) {
						this->minDistance = d;
						this->minIndex = j;
					}
					
				}

			}
		}

		if (this->minDistance != 0) {
			this->getArriveVectorFirstTime = true;
		}
	}

	if (!this->getArriveVectorFirstTime) {

		this->minIndex = 1000;
		for (auto& x : walls->exitPositions) {

			if (std::find(this->finishedPoints->begin(), this->finishedPoints->end(), x.first) == this->finishedPoints->end()) {
				if (x.first < minIndex) {
					minIndex = x.first;
				}
			}

		}

		if (walls->exitPositions.at(minIndex) != NULL) {

			if (location->distance(walls->exitPositions.at(minIndex)) < cfg->PATH_TO_FIND_RADIUS) {
				this->finishedPoints->push_back(minIndex);
			}

			return walls->exitPositions.at(minIndex);
		}
		else {
			return NULL;
		}
		
	}
	else {

		if (walls->exitPositions.at(minIndex) != NULL) {
			if ((walls->exitPositions.at(minIndex)->vec.y / walls->floorDiferencial) == this->floor) {

				if (location->distance(walls->exitPositions.at(minIndex)) < cfg->PATH_TO_FIND_RADIUS && !this->incrementedOnce) {
					++minIndex;
					this->incrementedOnce = true;
				}

				if (this->floor > 0) {

					if (this->startMovingToNextFloor) {

						
						escapeDuration = ((std::clock() - start) / (double)CLOCKS_PER_SEC) - (cfg->FLOOR_TIME_DURATION * this->floor); // escape time minus time for one floor

						if (escapeDuration > cfg->FLOOR_TIME_DURATION) {
							location->vec.y = walls->generatePositions->at(0).y;
							this->floor = 0;
							this->getArriveVectorFirstTime = false;
							this->incrementedOnce = false;
						}

					}
					if (location->distance(walls->exitPositions.at(minIndex)) < cfg->PATH_TO_FIND_RADIUS && !this->startMovingToNextFloor) {
						this->startMovingToNextFloor = true;
						start = std::clock();
					}
				}

				return walls->exitPositions.at(minIndex);
			}
			else {
				return NULL;
			}
		}
		else {
			return NULL;
		}
		

	}

}

void Boids::update()
{
	//if (!this->predator) {
		acceleration->mulScalar((float)(.4));
		velocity->addVector(acceleration);
		velocity->limit(maxSpeed);
		location->addVector(velocity);
		acceleration->mulScalar(0);
	//}
	//else {
		/*acceleration->mulScalar((float)(5.4));
		velocity->addVector(acceleration);
		velocity->limit(maxSpeed);
		location->addVector(velocity);
		acceleration->mulScalar(0);*/
	//}
}

void Boids::run(vector <Boids*> *v)
{
	flock(v);
	update();
}

void Boids::flock(vector<Boids*> *v)
{
	if (cfg->SEPARATION_ENABLED == 1) {
		this->tmpVectorMem = Separation(v);
		this->separationResult->set(
			this->tmpVectorMem->vec.x,
			this->tmpVectorMem->vec.y,
			this->tmpVectorMem->vec.z
		);
	}

	if (cfg->ALIGNMENT_ENABLED == 1 /*&& !this->predator*/) {
		this->tmpVectorMem = Alignment(v);
		this->aligmentResult->set(
			this->tmpVectorMem->vec.x,
			this->tmpVectorMem->vec.y,
			this->tmpVectorMem->vec.z
		);
	}

	if (cfg->COHESION_ENABLED == 1 /*&& !this->predator*/) {
		this->tmpVectorMem = Cohesion(v);
		this->cohesionResult->set(
			this->tmpVectorMem->vec.x,
			this->tmpVectorMem->vec.y,
			this->tmpVectorMem->vec.z
		);
	}

	this->tmpVectorMem = WallRepel();
	this->wallRepelResult->set(
		this->tmpVectorMem->vec.x,
		this->tmpVectorMem->vec.y,
		this->tmpVectorMem->vec.z
	);

	if (cfg->SCENE_TYPE == "2D") {
		this->tmpVectorMem = getArriveVector();
		this->arriveToResult->set();
	}

	if (this->tmpVectorMem != NULL) {
		this->tmpVectorMem = arriveTo(this->tmpVectorMem);
		this->arriveToResult->set(
			this->tmpVectorMem->vec.x,
			this->tmpVectorMem->vec.y,
			this->tmpVectorMem->vec.z
		);
	}

	if (cfg->SCENE_TYPE == "3D") {

		/*if (this->predator) {
			this->separationResult->mulScalar(10.5);
			applyForce(this->separationResult);
		}
		else {*/
			this->separationResult->mulScalar(1.5);
			this->aligmentResult->mulScalar(this->alignmentSensitivity);
			this->cohesionResult->mulScalar(0.4);
			applyForce(this->cohesionResult);
		//}
		
	}
	else {
		this->separationResult->mulScalar(0.75);
		this->aligmentResult->mulScalar(1.0);
		this->cohesionResult->mulScalar(0.5);
		this->arriveToResult->mulScalar(cfg->ESCAPE_SENSITIVITY);

		if (cfg->PATH_FINDING_ENABLED == 1) {
			if (this->wallRepelResult->vec.x == 0 && this->wallRepelResult->vec.y == 0) {
				applyForce(this->arriveToResult);
			}
		}
		
	}

	if (cfg->SEPARATION_ENABLED == 1) {
		applyForce(this->separationResult);
	}
	if (cfg->ALIGNMENT_ENABLED == 1 /*&& !this->predator*/) {
		if (this->wallRepelResult->vec.x == 0 && this->wallRepelResult->vec.y == 0) {
			applyForce(this->aligmentResult);
		}
	}
	if (cfg->COHESION_ENABLED == 1/* && !this->predator*/) {
		applyForce(this->cohesionResult);
	}

	applyForce(this->wallRepelResult);
}

MyVector *Boids::WallRepel() {
	
	this->oppositeVector->set();

	if (cfg->SCENE_TYPE == "3D") {

		if (cfg->BOID_SPACE_TYPE == "cube") {

			if (
				location->vec.x <= -this->cubeSize ||
				location->vec.x >= this->cubeSize ||
				location->vec.y <= -this->cubeSize ||
				location->vec.y >= this->cubeSize ||
				location->vec.z <= -this->cubeSize ||
				location->vec.z >= this->cubeSize
				) {
				this->oppositeVector->addVector(location);
				this->oppositeVector->mulScalar(-.0005);
				return this->oppositeVector;
			}
			else {
				this->oppositeVector->set();
				return this->oppositeVector;
			}

		}
		else if (cfg->BOID_SPACE_TYPE == "sphere") {

			if (location->distance(this->origin) > (cfg->BOID_CUBE_SIZE / 2)) {
			this->oppositeVector->addVector(location);
			this->oppositeVector->mulScalar(-.0001);
			return this->oppositeVector;
			}
			else {
			this->oppositeVector->set();
			return this->oppositeVector;
			}

		}

	}
	else {

		for (int i = 0, len = this->walls->size(); i < len; ++i) {

			Wall *tmpWall = this->walls->get(i);

			if (tmpWall->floor == this->floor) {

				this->desired->set();

				if (tmpWall->angle != 0) {

					this->desired->set(tmpWall->location->vec.x, 0, (float)tmpWall->location->vec.z);
					float d = location->distance(this->desired);

					if (d > 0 && d < cfg->WALL_AVOID_RADIUS) {
						return this->WallCollision(d, this->desired);
					}

				}
				else {

					this->desired->set((float)tmpWall->location->vec.x, 0, tmpWall->location->vec.z);
					float d = location->distance(this->desired);

					if (d > 0 && d < cfg->WALL_AVOID_RADIUS) {
						return this->WallCollision(d, this->desired);
					}

				}

			}

		}

		this->oppositeVector->set();
		return this->oppositeVector;
		
	}

}

MyVector *Boids::WallCollision(float direction, MyVector *_desired)
{
	this->tmpVector->set();
	this->tmpVectorMem = this->tmpVector;
	this->tmpVector = this->tmpVector->subTwoVector(location, _desired);
	this->tmpVector->normalize();
	this->tmpVector->divScalar(direction);
	this->oppositeVector->set(this->tmpVector->vec.x, this->tmpVector->vec.y, this->tmpVector->vec.z);
	delete this->tmpVector;
	this->tmpVector = this->tmpVectorMem;

	if (this->oppositeVector->magnitude() > 0) {
		this->oppositeVector->normalize();
		this->oppositeVector->mulScalar(maxSpeed);
		this->oppositeVector->subVector(velocity);
		this->oppositeVector->limit(maxForce);
	}

	return this->oppositeVector;
}

float Boids::angle(MyVector *v) const
{
	return (float)(atan2(v->vec.x, -v->vec.y));
}

float Boids::angleX(MyVector *v) const
{
	return (float)(atan2(v->vec.z, v->vec.y));
}

float Boids::angleY(MyVector *v) const
{
	return (float)(atan2(v->vec.x, v->vec.z));
}

float Boids::angleZ(MyVector *v) const
{
	return (float)(atan2(v->vec.y, v->vec.x));
}

float Boids::angleR(MyVector *v) const
{
	return (float)(sqrt(v->vec.x*v->vec.x + v->vec.y*v->vec.y + v->vec.z*v->vec.z));
}

float Boids::angleFi(MyVector *v) const
{
	return (float)(atan2(v->vec.x, v->vec.z));
}

float Boids::angleTheta(MyVector *v) const
{
	/*float r = angleR(v);
	return (float)(acos(v->vec.z / r));*/
	return (float)(atan2(hypot(v->vec.x, v->vec.z), v->vec.y));
}