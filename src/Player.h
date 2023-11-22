#pragma once

#include "SFML/Graphics.hpp"

#include "AnimationComponent.h"
#include "Logger.h"

class Player
{
public:
	Player();

	void processEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderWindow& window) const;

private:
	AnimationComponent animationComponent;

	sf::Sprite sprite;

};

