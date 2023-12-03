#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "SFML/Graphics.hpp"
#include "json.hpp"

#include "Logger.h"

static void loadAnimation(const std::string& dir, std::vector<sf::Texture>& animation, unsigned count);
static void loadSettings(const std::string& dir, nlohmann::json& json);

class AnimationComponent
{
private:
	struct Animation
	{
		unsigned count;
		unsigned time;  // ms
		bool looped;
		unsigned frame = 0;  // current
		std::vector<sf::Texture> frames;
	};

public:
	AnimationComponent();

	inline const sf::Texture& currentFrame() const;

	void setSprite(sf::Sprite* sprite);

	void load(const std::string& dirname);
	void change(const std::string& name);
	void update();

private:
	std::unordered_map<std::string, Animation> animation;
	Animation* current;
	sf::Clock clock;

	sf::Sprite* sprite;

	inline void updateTexture();
};

