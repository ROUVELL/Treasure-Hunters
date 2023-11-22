#pragma once

#include "SFML/Graphics.hpp"

class State
{
public:
	virtual void processEvents(const sf::Event& event) = 0;
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;
};

