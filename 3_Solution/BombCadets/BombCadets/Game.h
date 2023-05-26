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

#include "TextBox.h"


class Game
{
	std::string lobbyName;
	std::string lobbyPass;

	sf::RenderWindow* window;
	sf::RenderWindow* MENU;

	//RectangleShape logCreateBackground;
	//Texture logCreate_texture;
	//RectangleShape logBackground;
	//Texture log_texture;
	//RectangleShape createAccBackground;
	//Texture createAcc_texture;

	sf::RectangleShape skyBacc;
	sf::Texture sky_texture;
	
	//Character character;

	sf::Clock deltaClock;
	sf::Time deltaTime;

	bool focus;
	float musicVolume = 50.f;



public:
	Game();
	~Game();

	// Initializes game variables
	void start();

	static void startSinglePlayer();
	static void startMultiPlayer(std::string ip, unsigned short port);

	// Polls events
	void pollEvents();

	// Updates game logic
	void update();

	// Draws the game on the screen
	void draw();

	const sf::RenderWindow& getWindow() const;
};

