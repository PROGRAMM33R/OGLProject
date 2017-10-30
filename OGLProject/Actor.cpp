
#include "Actor.hpp"

Actor::Actor()
: Object(), velocity(0.0f), direction(0.0f) { }

Actor::Actor(glm::vec3 pos, glm::vec2 size, GLfloat direction, GLfloat velocity)
: Object(pos, size), velocity(velocity), direction(direction) { }

void Actor::move() {

	
}

