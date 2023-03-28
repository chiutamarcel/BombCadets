#include "Game.h"

#define PLAYERSIZE 50.0f
#define PLAYERSPEED 100.0f

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
	character(sf::Vector2f(0.0f, 0.0f), PLAYERSIZE, sf::Color::Blue, PLAYERSPEED)
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
	character.update(deltaTime.asSeconds());

	deltaTime = deltaClock.restart();
}

void Game::draw()
{
	// Clear screen
	window->clear();

	// Draw
	window->draw(character.getShape());

	// Display what has been drawn
	window->display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return *window;
}
