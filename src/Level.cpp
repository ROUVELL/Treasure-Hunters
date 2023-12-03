#include "Level.h"

#include <fstream>
#include <vector>
#include <cmath>

#include "Logger.h"

void Level::loadFromFile(const char* path)
{
	std::ifstream file(path);

	if (!file.is_open())
		Logger::logError("LEVEL: Can`t open the map file!");

	nlohmann::json json;
	try
	{
		json = nlohmann::json::parse(file);
	}
	catch (const std::exception& e)
	{
		Logger::logError("LEVEL: Error while parsing map file!", false);
		Logger::logError(e.what());
	}

	if (!json.is_object())
		Logger::logError("LEVEL: The map file must be json object (dict)!");

	parse(json);
}

void Level::addBlock(float x, float y)
{
	auto [i, j] = coordToIndex(x, y);

	size_t hash = indexToHash(i, j);
	if (blocks.contains(hash))
		return;

	const unsigned sum = getSum(i, j);

	sf::Sprite sprite;
	sprite.setPosition(static_cast<float>(i * 64), static_cast<float>(j * 64));
	sprite.setTexture(getTexture(sum));

	blocks[hash] = sprite;
	updateNeighbors(i, j);

	// Logger::logDebug("LEVEL: Block placed!  Pos: [" + std::to_string(static_cast<int>(x)) + ", " + std::to_string(static_cast<int>(y)) + "]   Index: [" + std::to_string(i) + ", " + std::to_string(j) + "]   Sum: " + std::to_string(sum) + "   Hash: " + std::to_string(hash));
}

void Level::deleteBlock(float x, float y)
{
	auto [i, j] = coordToIndex(x, y);
	size_t hash = indexToHash(i, j);

	if (!blocks.contains(hash))
		return;

	blocks.erase(hash);

	updateNeighbors(i, j);

	// Logger::logDebug("LEVEL: Block removed!  Pos: [" + std::to_string(static_cast<int>(x)) + ", " + std::to_string(static_cast<int>(y)) + "]   Index: [" + std::to_string(i) + ", " + std::to_string(j) + "]");
}

void Level::draw(sf::RenderWindow& window) const
{
	sf::RectangleShape shape{ sf::Vector2f{64, 64} };
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(-1);
	shape.setOutlineColor(sf::Color::Red);

	for (const auto& block : blocks)
	{
		window.draw(block.second);

		shape.setPosition(block.second.getPosition());
		window.draw(shape);
	}
}

void Level::parse(const nlohmann::json& json)
{
	const auto& j_blocks = json.find("blocks");

	if (j_blocks != json.end())
	{
		for (const auto& j_block : *j_blocks)
		{
			if (j_block.is_array() && j_block.size() == 2)
				addBlock(j_block[0], j_block[1]);
			else
				Logger::logWarning("LEVEL: Incorrect block position!");
		}
	}
	else
	{
		Logger::logWarning("LEVEL: No blocks have been loaded!");
	}
}

unsigned Level::getSum(int i, int j) const
{
	const int offsets[8][2] =
	{
		{-1, -1}, {0, -1}, {1, -1},
		{-1, 0},          { 1, 0},
		{-1, 1}, { 0, 1}, { 1, 1}
	};

	unsigned sum = 0;

	for (int k = 0; k < 8; k++)
	{
		int newI = i + offsets[k][0];
		int newJ = j + offsets[k][1];

		if (!blocks.contains(indexToHash(newI, newJ)))
			continue;

		sum += (1 << k);
	}

	return sum;
}

void Level::getNeighbors(int i, int j, std::vector<sf::Vector2i>* neighbors) const
{
	const int offsets[8][2] =
	{
		{-1, -1}, {0, -1}, {1, -1},
		{-1, 0},          { 1, 0},
		{-1, 1}, { 0, 1}, { 1, 1}
	};

	for (int k = 0; k < 8; k++)
	{
		int newI = i + offsets[k][0];
		int newJ = j + offsets[k][1];

		if (!blocks.contains(indexToHash(newI, newJ)))
			continue;

		neighbors->emplace_back(newI, newJ);
	}
}

void Level::updateNeighbors(int i, int j)
{
	std::vector<sf::Vector2i> neighbors;
	getNeighbors(i, j, &neighbors);

	for (const auto& [i, j] : neighbors)
		blocks[indexToHash(i, j)].setTexture(getTexture(getSum(i, j)));
}

sf::Texture& Level::getTexture(unsigned sum)
{
	if (!textures.contains(sum))
	{
		sf::Texture texture;
		texture.loadFromFile("./res/textures/terrarian/" + std::to_string(sum) + ".png");
		textures[sum] = texture;
	}

	return textures[sum];
}

inline std::size_t Level::indexToHash(int i, int j) const noexcept
{
	return (static_cast<size_t>(i) << 32) | static_cast<size_t>(j);
}

inline sf::Vector2i Level::coordToIndex(float x, float y) const noexcept
{
	return sf::Vector2i(static_cast<int>(std::floor(x / 64.f)), static_cast<int>(std::floor(y / 64.f)));
}
