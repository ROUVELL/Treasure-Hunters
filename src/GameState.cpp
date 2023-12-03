#include "GameState.h"

GameState::GameState(const GameData* gameData)
	: gameData(gameData)
{
	level.loadFromFile("./res/levels/level1.json");

	//Logger::logDebug("GameState: Initialization!");
}

void GameState::processEvents(const sf::Event& event)
{
	static sf::Vector2i mPos;
	static sf::Vector2f clickPos;

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		mPos = sf::Mouse::getPosition(*gameData->window);
		clickPos = gameData->window->mapPixelToCoords(mPos, *gameData->view);
		//Logger::logDebug("Mouse pressed at possition: [" + std::to_string(x) + ", " + std::to_string(y) + "]");

		if (event.mouseButton.button == sf::Mouse::Button::Left)
			level.addBlock(clickPos.x, clickPos.y);
		
		if (event.mouseButton.button == sf::Mouse::Button::Right)
			level.deleteBlock(clickPos.x, clickPos.y);

		break;

	default:
		break;
	}

	player.processEvents(event);
}

void GameState::update(float dt)
{
	player.update(dt);
}

void GameState::draw(sf::RenderWindow& window) const
{
	level.draw(window);
	player.draw(window);
}
