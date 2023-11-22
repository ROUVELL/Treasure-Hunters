#include "Game.h"

#include <fstream>

#include "GameState.h"
#include "Logger.h"


Game::Game() : gameData(&window, &view, &states), dt(0.16f)
{
	Logger::setLevel(Logger::Level::DEBUG);

	std::ifstream file(".\\res\\settings.json");

	if (!file.is_open())
	{
		Logger::logError("SETTINGS: Can`t open the settings json file!");
		return;
	}

	file >> settings;

	file.close();


	std::string title = settings["title"];

	if (settings.value("fullscreen", false))
		window.create(sf::VideoMode().getDesktopMode(), title, sf::Style::Fullscreen);
	else
	{
		unsigned width = settings["screen_width"];
		unsigned height = settings["screen_height"];
		window.create(sf::VideoMode(width, height), title);
	}

	window.setFramerateLimit(settings.value("fps", 60));
	window.setVerticalSyncEnabled(settings.value("vsync", true));
	
	auto [vWidth, vHeight] = window.getSize();
	view.reset(sf::FloatRect{ 0, 0, static_cast<float>(vWidth), static_cast<float>(vHeight) });
	//view.setViewport(sf::FloatRect{ 0.25, 0.25, 0.5, 0.5 });
	window.setView(view);

	states.push(std::make_shared<GameState>(&gameData));
}

void Game::run()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();

		processEvents();
		update();
		draw();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::Resized:
			window.setView(sf::View(sf::FloatRect(0.0, 0.0, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Left)
			{
				view.move(-10.0, 0.0);
				window.setView(view);
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				view.move(10.0, 0.0);
				window.setView(view);
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				view.move(0.0, -10.0);
				window.setView(view);
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				view.move(0.0, 10.0);
				window.setView(view);
			}
			break;

		default:
			break;
		}

		states.top()->processEvents(event);
	}
}

void Game::update()
{
	states.top()->update(dt);
}

void Game::draw()
{
	window.clear(sf::Color{30, 30, 30});

	states.top()->draw(window);

	window.display();
}
