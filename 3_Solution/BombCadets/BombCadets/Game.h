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
#include "JoinLobby.h"
#include "CreateLobby.h"
#include "LogCreate.h"
#include "LogIn.h"
#include "CreateAcc.h"
#include "InUsername.h"

#include "TextBox.h"


class Game
{
	string lobbyName;
	string lobbyPass;

	sf::RenderWindow* window;
	sf::RenderWindow* MENU;

	//RectangleShape logCreateBackground;
	//Texture logCreate_texture;
	//RectangleShape logBackground;
	//Texture log_texture;
	//RectangleShape createAccBackground;
	//Texture createAcc_texture;

	RectangleShape skyBacc;
	Texture sky_texture;

	RectangleShape bacc_game;
	Texture ba_texture;
	
	//Character character;

	sf::Clock deltaClock;
	sf::Time deltaTime;

	float musicVolume = 50.f;

	Text disp_player;
	Font font;

	std::string mapFileName;

public:
	Game();
	~Game();

	// Initializes game variables
	void start();

	static void startSinglePlayer();
	static void startMultiPlayer();

	// Polls events
	void pollEvents();

	// Updates game logic
	void update();

	// Draws the game on the screen
	void draw();

	const sf::RenderWindow& getWindow() const;
};

