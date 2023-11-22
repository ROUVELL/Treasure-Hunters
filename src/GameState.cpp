#include "GameState.h"

GameState::GameState(const GameData* gameData)
	: gameData(gameData)
{
	level.loadFromFile("./res/levels/level1.json");

	//Logger::logDebug("GameState: Initialization!");
}

void GameState::processEvents(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			sf::Vector2i mPos = sf::Mouse::getPosition(*gameData->window);
			auto [x, y] = gameData->window->mapPixelToCoords(mPos, *gameData->view);
			//Logger::logDebug("Mouse pressed at possition: [" + std::to_string(x) + ", " + std::to_string(y) + "]");
			level.addBlock(static_cast<float>(x), static_cast<float>(y));
		}
		break;

	default:
		break;
	}

	player.processEvents(event);
}

void GameState::update(float dt)
{
	player.update();
}

void GameState::draw(sf::RenderWindow& window) const
{
	level.draw(window);
	player.draw(window);
}
