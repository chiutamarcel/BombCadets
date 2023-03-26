#include "Game.h"

void Game::pollEvents()
{
	// Process events
	sf::Event event;
	while (window->pollEvent(event))
	{
		// Close window: exit
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

Game::Game()
{
	window = nullptr;
	circle = nullptr;
}

Game::~Game()
{
	if (window != nullptr)
		delete window;

	if (circle != nullptr)
		delete circle;
}

void Game::start()
{
	window = new sf::RenderWindow(
		sf::VideoMode(800, 600), 
		"SFML window"
	);

	circle = new sf::CircleShape();
	circle->setFillColor(sf::Color::Red);
	circle->setRadius(100.0f);
	circle->setScale(sf::Vector2f(1.0f, 1.0f));
}

void Game::update()
{
}

void Game::draw()
{
	window->clear();

	window->draw(*circle);

	window->display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return *window;
}
