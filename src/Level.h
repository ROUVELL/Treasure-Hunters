#pragma once

#include <unordered_map>

#include "SFML/Graphics.hpp"
#include "json.hpp"

class Level
{
public:
	void loadFromFile(const char* path);

	void addBlock(float x, float y);
	void deleteBlock(float x, float y);
	
	void draw(sf::RenderWindow& window) const;

private:
	std::unordered_map<std::size_t, sf::Sprite> blocks;
	std::unordered_map<unsigned, sf::Texture> textures;

	void parse(const nlohmann::json& json);
	void updateNeighbors(int i, int j);

	unsigned getSum(int i, int j) const;
	void getNeighbors(int i, int j, std::vector<sf::Vector2i>* neighbors) const;
	sf::Texture& getTexture(unsigned sum);

	inline std::size_t indexToHash(int i, int j) const noexcept;
	inline sf::Vector2i coordToIndex(float x, float y) const noexcept;
};

