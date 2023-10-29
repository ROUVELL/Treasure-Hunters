#pragma once

#include "SFML/Graphics.hpp"

#include "AnimationComponent.h"
#include "Logger.h"

class Player
{
public:
	Player();

	void processEvents(sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target) const;

private:
	AnimationComponent animationComponent;

	sf::Sprite sprite;

};

