#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Entity.h"
#include "Character.h"
#include "Block.h"
#include "Entities.h"

class Game
{
	sf::RenderWindow* window;
	
	//Character character;

	sf::Clock deltaClock;
	sf::Time deltaTime;

public:

	Game();
	~Game();

	// Initializes game variables
	void start();

	// Generates the map
	void generateMap();

	// Polls events
	void pollEvents();

	// Updates game logic
	void update();

	// Draws the game on the screen
	void draw();

	const sf::RenderWindow& getWindow() const;
};

