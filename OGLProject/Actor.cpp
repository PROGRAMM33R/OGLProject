
#include "Actor.hpp"

Actor::Actor()
: Object(), Velocity(0.0f), Direction(1, 0) { }

Actor::Actor(glm::vec3 pos, glm::vec2 size, glm::vec2 direction, glm::vec3 color = glm::vec3(1.0f), float velocity = 0.0f)
: Object(pos, size, color), Velocity(velocity), Direction(direction) { }

void Actor::Draw(Model &renderer) {
	// renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}