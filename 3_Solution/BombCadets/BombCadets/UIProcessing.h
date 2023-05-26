#pragma once
#include "Game.h"
#include "GameConfig.h"

class UIProcessing {
public:
    static UIProcessing& get();

    UIProcessing(const UIProcessing&) = delete;
    UIProcessing& operator=(const UIProcessing&) = delete;

    static void destruct();
	void draw(RenderWindow* window);

    void processEvents(Event event, RenderWindow* window, MENUTYPE &curMenu, GAMESTATE &curGameState, ENTRYTYPE &curEntryType);

	string lobbyName;
	string lobbyPass;

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

	void switchMenu(MENUTYPE curMenu)
	{
		delete curUI;

		switch (curMenu)
		{
		case MENUTYPE::MAINMENU:
			curUI = new MainMenu(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
			break;
		case MENUTYPE::PLAY:
			curUI = new PlayMode(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
			break;
		case MENUTYPE::ABOUT:
			curUI = new AboutMode(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
			break;
		case MENUTYPE::HIGHSCORES:
			curUI = new HighScore(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
			break;
		case MENUTYPE::OPTIONS:
			curUI = new Options(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
			break;
		case MENUTYPE::JOINLOBBY:
			curUI = new JoinLobby(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
			break;
		case MENUTYPE::CREATELOBBY:
			curUI = new CreateLobby(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
			break;
		}
	}

private:
	UIProcessing()
	{
		if (!music.openFromFile("Media\\bacc.wav"))
			exit(1); // eroare
		music.play();
		music.setLoop(true);
		music.setVolume(musicVolume);

		curUI = new InUsername(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
	}
    ~UIProcessing() = default;
    static UIProcessing* instance; 
	Menu* curUI;
};

