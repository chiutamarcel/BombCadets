#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Entity.h"
#include "Player.h"

class Game
{
	sf::RenderWindow* window;

	Player player;

	sf::Clock deltaClock;
	sf::Time deltaTime;

public:

	Game();
	~Game();

	// Initializes game variables
	void start();

	// Polls events
	void pollEvents();

	// Updates game logic
	void update();

	// Draws the game on the screen
	void draw();

	const sf::RenderWindow& getWindow() const;
};

