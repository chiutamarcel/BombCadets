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

Game::Game() : 
	entity(sf::Vector2f(0.0f, 0.0f), 50.0f, sf::Color::Blue)
{
	window = nullptr;
}

Game::~Game()
{
	if (window != nullptr)
		delete window;
}

void Game::start()
{
	window = new sf::RenderWindow(
		sf::VideoMode(800, 600), 
		"SFML window"
	);
}

void Game::update()
{
	entity.update();
}

void Game::draw()
{
	// Clear screen
	window->clear();

	// Draw
	window->draw(entity.getShape());

	// Display what has been drawn
	window->display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return *window;
}
