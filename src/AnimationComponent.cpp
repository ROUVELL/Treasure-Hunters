#include "AnimationComponent.h"

void loadAnimation(const std::string& path, std::vector<sf::Texture>& animation, unsigned count)
{
	// Logger::logDebug("ANIMATION_LOADER: Start loading " + std::to_string(count) + " animations from '" + path + "'");

	if (count == 0)
		Logger::logWarning("ANIMATION_LOADER: Parametr 'count' set to zero!");


	for (unsigned i = 1; i <= count; ++i)
	{
		sf::Texture texture;
		texture.loadFromFile(path + std::to_string(i) + ".png");

		animation.push_back(texture);
	}
}

void loadSettings(const std::string& dir, nlohmann::json& json)
{
	std::ifstream file(dir + "\\animation.json");

	if (!file.is_open())
		Logger::logError("ANIMATION_COMPONENT: Can`t open the animation settings file!");

	try
	{
		json = nlohmann::json::parse(file);
	}
	catch (const std::exception& e)
	{
		Logger::logError("ANIMATION_COMPONENT: Error while parsing animation settings file!", false);
		Logger::logError(e.what());
	}

	if (!json.is_array())
	{
		Logger::logError("ANIMATION_COMPONENT: Animation settings json file must be array!");
	}
}

AnimationComponent::AnimationComponent()
	: current(nullptr), sprite(nullptr)
{

}

inline void AnimationComponent::updateTexture()
{
	if (this->sprite != nullptr)
	{
		this->sprite->setTexture(currentFrame());
		clock.restart();
	}
}

inline const sf::Texture& AnimationComponent::currentFrame() const
{
	return current->frames[current->frame];
}

void AnimationComponent::setSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

void AnimationComponent::load(const std::string& dirname)
{
	const std::string rootDir = ".\\res\\sprites\\" + dirname;

	nlohmann::json json;
	loadSettings(rootDir, json);

	size_t count_all = 0;

	for (const auto& item : json)
	{
		if (!item.is_object())
		{
			Logger::logWarning("ANIMATION_COMPONENT: Non-object item was skiped!");
			continue;
		}

		std::string dir;
		unsigned count;
		unsigned time;
		bool looped;

		try
		{
			dir = item["dir"];
			count = item["count"];
			time = item.value("time", 100U);
			looped = item.value("looped", true);
		}
		catch (const std::exception& e)
		{
			Logger::logError("ANIMATION_COMPONENT: Error while reading animation settings! Try looking at the file!", false);
			Logger::logError(e.what(), false);
			Logger::logWarning("ANIMATION_COMPONENT: Bad object was skiped!");
			continue;
		}

		count_all += count;

		Animation anim{count, time, looped};

		loadAnimation(rootDir + "\\" + dir + "\\", anim.frames, count);

		animation[dir] = anim;
	}

	Logger::logInfo("ANIMATION_COMPONENT: All animations using: " + std::to_string(sizeof(sf::Texture) * count_all) + " Kb of memory!");
}

void AnimationComponent::change(const std::string& name)
{
	if (!animation.contains(name))
	{
		Logger::logError("ANIMATION_COMPONENT: Animation '" + name + "' not found!", false);
		return;
	}

	if (current == &animation[name])
		return;

	if (current != nullptr)
		current->frame = 0;

	current = &animation[name];
	updateTexture();

	Logger::logDebug("ANIMATION_COMPONENT: Animation changed to '" + name + "'");
}

void AnimationComponent::update()
{
	if (static_cast<unsigned>(clock.getElapsedTime().asMilliseconds()) > current->time)
	{
		if (++current->frame >= current->count)
			current->frame = current->looped ? 0 : current->count - 1;

		updateTexture();
	}
}
