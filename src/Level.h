#pragma once

#include <unordered_map>

#include "SFML/Graphics.hpp"
#include "json.hpp"

class Level
{
public:
	void loadFromFile(const char* path);

	void addBlock(float x, float y);
	
	void draw(sf::RenderWindow& window) const;

private:
	std::unordered_map<std::size_t, sf::Sprite> blocks;
	std::unordered_map<unsigned, sf::Texture> textures;

	void parse(const nlohmann::json& json);
	unsigned getSum(int i, int j, std::vector<sf::Vector2i>* neigboars = nullptr) const;
	sf::Texture& getTexture(unsigned sum);

	inline std::size_t IndexToHash(int x, int y) const noexcept;
};

