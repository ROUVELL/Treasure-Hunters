#pragma once

#include <stack>
#include <memory>

#include "State.h"

struct GameData
{
	const sf::RenderWindow* window;
	const sf::View* view;

	const std::stack<std::shared_ptr<State>>* states;

	GameData(sf::RenderWindow* window, sf::View* view, std::stack<std::shared_ptr<State>>* states)
		: window(window), view(view), states(states) { }
};

