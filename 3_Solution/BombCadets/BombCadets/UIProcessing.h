#pragma once
#include "Game.h"
#include "GameConfig.h"
#include "Menu.h"

class UIProcessing {
public:
    static UIProcessing& get();

    UIProcessing(const UIProcessing&) = delete;
    UIProcessing& operator=(const UIProcessing&) = delete;

    static void destruct();
	void draw(sf::RenderWindow* window);

    void processEvents(sf::Event event, sf::RenderWindow* window, MENUTYPE &curMenu, GAMESTATE &curGameState, ENTRYTYPE &curEntryType);

	std::string lobbyName;
	std::string lobbyPass;

	//MainMenu* mainMenu = new MainMenu(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
	//PlayMode* playMode;
	//AboutMode* about;
	//HighScore* highScore;
	//Options* options;
	//JoinLobby* joinLobby;
	//CreateLobby* createLobby;
	///*TextBox createLobb;
	//TextBox createPass;
	//TextBox joinLobb;
	//TextBox userTextBox;*/
	//InUsername* inUsername;

	//TextBox logUsername;
	//TextBox logPassword;
	//TextBox createUsername;
	//TextBox createPassword;
	//LogCreate* logCreate;
	//LogIn* Login;
	//CreateAcc* createAcc;

	//Character character;

	sf::Clock deltaClock;
	sf::Time deltaTime;

	float musicVolume = 50.f;
	sf::Music music;
	sf::Music gameMusic;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	void switchMenu(MENUTYPE curMenu);

private:
	UIProcessing();
    ~UIProcessing() = default;
    static UIProcessing* instance; 
	Menu* curUI;
};

