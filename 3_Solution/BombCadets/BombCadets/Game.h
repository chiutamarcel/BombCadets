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

#include "MainMenu.h"
#include "PlayMode.h"
#include "AboutMode.h"
#include "HighScore.h"
#include "Options.h"

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
	RectangleShape highBackground;
	Texture high_texture;
	RectangleShape optionsBackground;
	Texture options_texture;

	MainMenu* mainMenu;
	PlayMode* playMode;
	AboutMode* about;
	HighScore* highScore;
	Options* options;
	
	//Character character;

	sf::Clock deltaClock;
	sf::Time deltaTime;

	bool focus;

public:

	Game();
	~Game();

	// Initializes game variables
	void start();

	void startSinglePlayer();
	void startMultiPlayer();

	// Polls events
	void pollEvents();

	// Updates game logic
	void update();

	// Draws the game on the screen
	void draw();

	const sf::RenderWindow& getWindow() const;
};

