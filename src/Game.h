#pragma once

#include "Player.h"
#include "Settings.h"


class Game
{
public:
	Game();
	~Game();

	void run();

private:

	sf::RenderWindow* window;

	Player* player;
	Settings* settings;

	void processEvents();
	void update();
	void draw() const;
};

