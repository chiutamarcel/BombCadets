#include "Game.h"
#include <fstream>

#define ENTITYSIZE 64.0f
#define PLAYERSIZE 64.0f
#define PLAYERSPEED 100.0f
#define WINDOWXSIZE 1344
#define WINDOWYSIZE 832
#define NRBREAKABLEWALLS 70

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


Game::Game(){}

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
	generateMap();
}

void Game::generateMap()
{
	// read from a file the map
	std::ifstream map("map.txt");

	if(!map.is_open())
	{
		std::cout << "Error opening map file" << std::endl;
		exit(1);
	}
	// alloc the map matrix
	char** mapMatrix = new char* [(int)(WINDOWYSIZE / ENTITYSIZE)];
	for (int i = 0; i < (int)(WINDOWYSIZE / ENTITYSIZE); i++)
	{
		mapMatrix[i] = new char[(int)(WINDOWXSIZE / ENTITYSIZE) + 1];
	}

	// read the map
	char type;
	for (int i = 0; i < WINDOWYSIZE / ENTITYSIZE; i++)
		for (int j = 0; j < WINDOWXSIZE / ENTITYSIZE + 1; j++)
		{
			map.get(type);
			mapMatrix[i][j] = type;
			
		}
	map.close();
	// randomly generate the breakable walls
	int numberOfBreakableWalls = NRBREAKABLEWALLS;
	while (numberOfBreakableWalls)
	{
		//srand(time(NULL));
		int i = (rand() % ((int)(WINDOWYSIZE / ENTITYSIZE) - 4)) + 3;
		int j = (rand() % ((int)(WINDOWXSIZE / ENTITYSIZE) - 2)) + 1;
		if (mapMatrix[i][j] == '0')
		{
			mapMatrix[i][j] = '2';
			numberOfBreakableWalls--;
		}
	}
	
	// generate the map
	for(int i=0; i < WINDOWYSIZE / ENTITYSIZE ; i++, std::cout<<std::endl)
		for (int j = 0; j < WINDOWXSIZE / ENTITYSIZE; j++)
		{
			std::cout << mapMatrix[i][j];
			switch (mapMatrix[i][j])
			{
			case '1':
				//create a wall
				Entities::getInstance().getWalls().push_back(new Block(sf::Vector2f(j * ENTITYSIZE, i * ENTITYSIZE), ENTITYSIZE, sf::Color::Green));
				break;
			case '2':
				//create brakable block
				Entities::getInstance().getBreakableBlocks().push_back(new BreakableBlock(sf::Vector2f(j * ENTITYSIZE, i * ENTITYSIZE), ENTITYSIZE, sf::Color::Red));
				break;
			case '3':
				//create player
				Entities::getInstance().getCharacters().push_back(new Character(sf::Vector2f(j * ENTITYSIZE, i * ENTITYSIZE), PLAYERSIZE, sf::Color::Blue, PLAYERSPEED));
				break;
			case '4':
				//generate AI
				break;
			case 'z':
				//generate menu
				break;
			default:
				break;
			}
		}
	std::cout << std::endl;

	for (int i = 0; i < (int)(WINDOWYSIZE / ENTITYSIZE); i++)
	{
		delete[] mapMatrix[i];
	}
	delete[] mapMatrix;
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
	//for (auto entity : Entities::getInstance().getExplosions())
	//{
	//	//if(entity == previous)
	//	std::cout << entity << std::endl;
	//	auto previous = entity;
	//	entity->update(deltaTime.asSeconds());
	//	
	//}
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
