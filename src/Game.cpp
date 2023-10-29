#include "Game.h"

Game::Game()
{
	Logger::setLevel(Logger::Level::DEBUG);

	player = new Player;
	settings = new Settings;

	std::string title = settings->get<std::string>("title");

	if (settings->get("fullscreen", false))
		window = new sf::RenderWindow(sf::VideoMode().getDesktopMode(), title, sf::Style::Fullscreen);
	else
	{
		unsigned width = settings->get<unsigned>("screen_width");
		unsigned height = settings->get<unsigned>("screen_height");
		window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	}

	window->setFramerateLimit(settings->get("fps", 60));
	window->setVerticalSyncEnabled(settings->get("vsync", true));
}

Game::~Game()
{
	delete player;
	player = nullptr;

	delete settings;
	settings = nullptr;

	delete window;
	window = nullptr;
}

void Game::run()
{
	sf::Clock clock;

	while (window->isOpen())
	{
		processEvents();
		update();
		draw();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		default:
			break;
		}

		player->processEvents(event);
	}
}

void Game::update()
{
	this->player->update();
}

void Game::draw() const
{
	window->clear(sf::Color{30, 30, 30});

	player->draw(*window);

	window->display();
}
