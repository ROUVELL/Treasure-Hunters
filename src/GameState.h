#pragma once

#include "GameData.h"
#include "Player.h"
#include "Level.h"

class GameState : public State
{
public:
	GameState(const GameData* gameData);

	void processEvents(const sf::Event& event) override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) const override;

private:
	const GameData* gameData;

	Player player;
	Level level;
};

