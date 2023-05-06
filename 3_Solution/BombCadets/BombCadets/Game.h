#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Entity.h"
#include "Character.h"

#include "MainMenu.h"
#include "PlayMode.h"
#include "AboutMode.h"

class Game
{
	sf::RenderWindow* window;
	sf::RenderWindow* MENU;

	RectangleShape background;
	Texture Maintexture;
	RectangleShape playBackground;
	Texture play_texture;
	RectangleShape aboutBackground;
	Texture about_texture;

	MainMenu* mainMenu;
	PlayMode* playMode;
	AboutMode* about;

	Character character;

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

