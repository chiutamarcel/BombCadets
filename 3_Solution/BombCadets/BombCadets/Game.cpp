#include "Game.h"
#include "Map.h"
#include "GameConfig.h"
#include <utility>
#include <fstream>

using namespace GameConfig;

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


Game::Game(){
	mapFileName = "map.txt";
}

Game::~Game()
{
	if (window != nullptr)
		delete window;
}

void Game::start()
{
	window = new sf::RenderWindow(
		sf::VideoMode(WINDOWXSIZE, WINDOWYSIZE), 
		"SFML window"
	);
	Map::readFromFile(mapFileName);
}

void Game::update()
{
	//character.update(deltaTime.asSeconds());
	for (auto entity : Entities::getInstance().getCharacters())
		entity->update(deltaTime.asSeconds());
	for (auto entity : Entities::getInstance().getBreakableBlocks())
		entity->update(deltaTime.asSeconds());
	for (auto entity : Entities::getInstance().getBombs())
		entity->update(deltaTime.asSeconds());

	std::vector<Explosion*>& explosions = Entities::getInstance().getExplosions();
	for (int i = 0; i < explosions.size(); i++)
		(explosions[i])->update(deltaTime.asSeconds());
	
	deltaTime = deltaClock.restart();
}

void Game::draw()
{
	// Clear screen
	window->clear();

	// Draw
	for (auto entity : Entities::getInstance().getCharacters())
		window->draw(entity->getShape());
	for (auto entity : Entities::getInstance().getBreakableBlocks())
		window->draw(entity->getShape());
	for (auto entity : Entities::getInstance().getBombs())
		window->draw(entity->getShape());
	for (auto entity : Entities::getInstance().getWalls())
		window->draw(entity->getShape());
	for (auto entity : Entities::getInstance().getExplosions())
		window->draw(entity->getShape());

	// Display what has been drawn
	window->display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return *window;
}
