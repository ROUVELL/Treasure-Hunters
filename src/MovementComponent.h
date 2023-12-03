#pragma once

#include "SFML/Graphics.hpp"

#include "enums.h"

class MovementComponent
{
public:
	MovementComponent();

	MovementState getState() const;

	float getVelocityX() const { return velocity.x; }
	float getVelocityY() const { return velocity.y; }

	void setSprite(sf::Sprite* sprite) { this->sprite = sprite; }
	
	void setSpeed(float speed) { this->speed = speed; }
	void setDirection(Direction dir) { this->direction = static_cast<float>(dir); }
	//void setGravity(float value) { this->gravity = value; }

	//void turnGravityOff() { gravity = 0.0; }
	//void turnGravityOn(float value) { gravity = value; }

	void update(float dt);

private:
	float speed;
	float direction;

	sf::Vector2f velocity;

	sf::Sprite* sprite;
};

