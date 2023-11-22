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
	const int i = static_cast<int>(std::floor(x / 64.f));
	const int j = static_cast<int>(std::floor(y / 64.f));

	size_t hash = IndexToHash(i, j);
	if (blocks.contains(hash))
		return;

	sf::Sprite sprite;
	sprite.setPosition(static_cast<float>(i * 64), static_cast<float>(j * 64));

	std::vector<sf::Vector2i> neigboars;
	const unsigned sum = getSum(i, j, &neigboars);

	sprite.setTexture(getTexture(sum));

	blocks[hash] = sprite;
	Logger::logDebug("LEVEL: Pos: [" + std::to_string(static_cast<int>(x)) + ", " + std::to_string(static_cast<int>(y)) + "]   Index: [" + std::to_string(i) + ", " + std::to_string(j) + "]   Sum: " + std::to_string(sum) + "   Hash: " + std::to_string(hash));

	for (const auto& vec : neigboars)
	{
		unsigned sum = getSum(vec.x, vec.y);
		blocks[IndexToHash(vec.x, vec.y)].setTexture(getTexture(sum));
	}
}

void Level::draw(sf::RenderWindow& window) const
{
	for (const auto& block : blocks)
		window.draw(block.second);
}

void Level::parse(const nlohmann::json& json)
{
	const auto& j_blocks = json.find("blocks");

	if (j_blocks != json.end())
	{
		for (const auto& j_block : *j_blocks)
		{
			addBlock(j_block[0], j_block[1]);
		}
	}
	else
	{
		Logger::logWarning("LEVEL: No blocks have been loaded!");
	}
}

unsigned Level::getSum(int i, int j, std::vector<sf::Vector2i>* neigboars) const
{
	int offsets[8][2] =
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

		if (!blocks.contains(IndexToHash(newI, newJ)))
			continue;

		if (neigboars != nullptr)
			neigboars->push_back(sf::Vector2i(newI, newJ));

		sum += (1 << k);
	}

	return sum;
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

std::size_t Level::IndexToHash(int x, int y) const noexcept
{
	return (static_cast<size_t>(x) << 32) | static_cast<size_t>(y);
}
