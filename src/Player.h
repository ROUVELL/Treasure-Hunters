#pragma once

#include "SFML/Graphics.hpp"

#include "AnimationComponent.h"
#include "MovementComponent.h"

class Player
{
public:
	Player();

	void processEvents(const sf::Event& event);

	void movement();
	void checkState();

	void update(float dt);
	void draw(sf::RenderWindow& window) const;

private:
	AnimationComponent animationComponent;
	MovementComponent movementComponent;

	sf::Sprite sprite;
	sf::RectangleShape shape;

};

