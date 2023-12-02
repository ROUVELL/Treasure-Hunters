#pragma once

#include "json.hpp"

#include "GameData.h"

class Game
{
public:
	Game();

	void run();

private:
	GameData gameData;
	sf::RenderWindow window;
	sf::View view;
	sf::Text fps;
	sf::Font fpsFont;

	nlohmann::json settings;

	std::stack<std::shared_ptr<State>> states;
	
	float dt;


	void processEvents();
	void update();
	void draw();
};

