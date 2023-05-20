#include "Game.h"
#include "Map.h"
#include "Client.h"
#include "GameConfig.h"
#include <utility>
#include <fstream>

using namespace GameConfig;

enum class GAMESTATE { MAINMENU, INGAME };
enum class MENUTYPE { MAINMENU, PLAY, OPTIONS, HIGHSCORES, ABOUT, JOINLOBBY, CREATELOBBY };
MENUTYPE curMenu;
GAMESTATE curGameState;

Game::Game() {
    focus = true;
}

void Game::pollEvents()
{
    Client::getInstance().pollEvents();

    if (curGameState == GAMESTATE::INGAME) {
        if (focus == true) {
            Entities::getInstance().getPlayer().pollEvents();
        }
    }

    // Process events
    sf::Event event;
    
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::GainedFocus) {
            focus = true;
        }
        
        if (event.type == sf::Event::LostFocus) {
            focus = false;
        }

        if (curGameState == GAMESTATE::INGAME) {
            if (event.type == Event::Closed) {
                window->close();
                return;
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window->close();
                    return;
                }
            }
        } else if (curGameState == GAMESTATE::MAINMENU) {
            switch (curMenu) {
            case MENUTYPE::MAINMENU:
                if (event.type == Event::Closed) {
                    window->close();
                }
                if (event.type == Event::KeyReleased) {
                    if (event.key.code == Keyboard::Up) {
                        mainMenu->MoveUp();
                        break;
                    }

                    if (event.key.code == Keyboard::Down) {
                        mainMenu->MoveDown();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int x = mainMenu->MainMenuPressed();
                        switch (x) {
                        case 0:
                            playMode = new PlayMode(WINDOWXSIZE, WINDOWYSIZE);
                            curMenu = MENUTYPE::PLAY;
                            break;
                        case 1:
                            options = new Options(WINDOWXSIZE, WINDOWYSIZE);
                            curMenu = MENUTYPE::OPTIONS;
                            break;
                        case 2:
                            highScore = new HighScore(WINDOWXSIZE, WINDOWYSIZE);
                            curMenu = MENUTYPE::HIGHSCORES;
                            break;
                        case 3:
                            about = new AboutMode(WINDOWXSIZE, WINDOWYSIZE);
                            curMenu = MENUTYPE::ABOUT;
                            break;
                        case 4:
                            exit(0);
                            break;
                        }
                    }
                }
                break;
            case MENUTYPE::PLAY:
                if (event.type == Event::Closed) {
                    curMenu = MENUTYPE::MAINMENU;
                    delete playMode;
                    break;
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        curMenu = MENUTYPE::MAINMENU;
                        delete playMode;
                        break;
                    }
                }

                if (event.type == Event::KeyReleased) {
                    if (event.key.code == Keyboard::Left) {
                        playMode->left();
                        break;
                    }

                    if (event.key.code == Keyboard::Right) {
                        playMode->right();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int y = playMode->buttonPressed();

                        if (y == 0)
                        {
                            //create lobby
                            //startSinglePlayer();
                            createLobby = new CreateLobby(WINDOWXSIZE, WINDOWYSIZE);
                            testText = TextBox(50, sf::Color::White, true);
                            testText.setFont();
                            testText.setPosition({ 110, 280 });
                            curMenu = MENUTYPE::CREATELOBBY;
                            break;
                        }

                        if (y == 1)
                        {
                            //join lobby
                            joinLobby = new JoinLobby(WINDOWXSIZE, WINDOWYSIZE);
                            curMenu = MENUTYPE::JOINLOBBY;
                            break;
                        }
                    }
                }
                break;

            case MENUTYPE::ABOUT:

                if (event.type == Event::Closed) {
                    curMenu = MENUTYPE::MAINMENU;
                    break;
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        curMenu = MENUTYPE::MAINMENU;
                        break;
                    }
                }

                if (event.type == Event::KeyReleased) {
                    if (event.key.code == Keyboard::Up) {
                        about->up();
                        break;
                    }

                    if (event.key.code == Keyboard::Down) {
                        about->down();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int y = about->buttonPressed();

                        if (y == 0)
                        {
                            //how to play
                        }

                        if (y == 1)
                        {
                            //controls
                        }
                    }

                }

                break;
            case MENUTYPE::HIGHSCORES:

                if (event.type == Event::Closed) {
                    curMenu = MENUTYPE::MAINMENU;
                    break;
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        curMenu = MENUTYPE::MAINMENU;
                        break;
                    }
                }

                if (event.type == Event::KeyReleased) {
                    if (event.key.code == Keyboard::Up) {
                        highScore->up();
                        break;
                    }

                    if (event.key.code == Keyboard::Down) {
                        highScore->down();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int y = highScore->buttonPressed();

                        if (y == 0)
                        {
                            //local
                        }

                        if (y == 1)
                        {
                            //regional
                        }
                    }

                }

                break;
            case MENUTYPE::OPTIONS:

                if (event.type == Event::Closed) {
                    curMenu = MENUTYPE::MAINMENU;
                    break;
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        curMenu = MENUTYPE::MAINMENU;
                        break;
                    }
                }

                if (event.type == Event::KeyReleased) {
                    if (event.key.code == Keyboard::Up) {
                        options->up();
                        break;
                    }

                    if (event.key.code == Keyboard::Down) {
                        options->down();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int y = options->buttonPressed();

                        if (y == 0)
                        {
                            //player skin
                        }

                        if (y == 1)
                        {
                            //bomb skin
                        }

                        if (y == 2)
                        {
                            //sound
                        }
                    }

                }

                break;
            default:

                if (event.type == Event::Closed) {
                    curMenu = MENUTYPE::MAINMENU;
                    break;
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        curMenu = MENUTYPE::MAINMENU;
                        break;
                    }
                }

                break;

            }
        }
    }
}


Game::~Game()
{
	if (window != nullptr)
		delete window;
}

void Game::start()
{

	// Make Main window
    window = new sf::RenderWindow(VideoMode(WINDOWXSIZE, WINDOWYSIZE), "Bomberman");
	mainMenu = new MainMenu(WINDOWXSIZE, WINDOWYSIZE);

	//set background
	background.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
	Maintexture.loadFromFile("Textures\\mainbackground.png");
	background.setTexture(&Maintexture);

	//Play bacc
	playBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
	play_texture.loadFromFile("Textures\\afterplay.png");
	playBackground.setTexture(&play_texture);

	//About bacc
	aboutBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
	about_texture.loadFromFile("Textures\\about.png");
	aboutBackground.setTexture(&about_texture);

    //highscores bacc
    highBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
    high_texture.loadFromFile("Textures\\highsc.png");
    highBackground.setTexture(&high_texture);

    //options bacc
    optionsBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
    options_texture.loadFromFile("Textures\\optionen.png");
    optionsBackground.setTexture(&options_texture);

    //join bacc
    joinBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
    join_texture.loadFromFile("Textures\\joinLobby.png");
    joinBackground.setTexture(&join_texture);

    //create bacc
    createBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
    create_texture.loadFromFile("Textures\\createLobby.png");
    createBackground.setTexture(&create_texture);

    curMenu = MENUTYPE::MAINMENU;
    curGameState = GAMESTATE::MAINMENU;
}

void Game::update()
{
	if (curGameState == GAMESTATE::INGAME) {
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
}

void Game::startSinglePlayer() {
    curGameState = GAMESTATE::INGAME;
    MapText mapText(BLOCKSONSCREENX, BLOCKSONSCREENY);
    mapText.readFromFile(mapFile);
    mapText.putBreakableBlocks(NRBREAKABLEWALLS);
    Map::spawnMap(mapText);
    Map::spawnCharacter(Map::CharacterType::PLAYER);
    Map::spawnCharacter(Map::CharacterType::BOT);
}

void Game::startMultiPlayer() {
    curGameState = GAMESTATE::INGAME;
    Client::getInstance().start();

    // TODO: change later after adding a proper Bot class
    for (int i = 0; i < Map::maxPlayers; i++) {
        if (i == Client::getInstance().getId()) {
            Map::spawnCharacter(Map::CharacterType::PLAYER);
        }
        else {
            Map::spawnCharacter(Map::CharacterType::BASE);
        }
    }
}

void Game::draw()
{
	// Clear screen
	window->clear();

	// Draw
    if (curGameState == GAMESTATE::MAINMENU) {
        switch (curMenu) {
        case MENUTYPE::MAINMENU:
            window->draw(background);
            mainMenu->draw(*window);
            break;
        case MENUTYPE::PLAY:
            window->draw(playBackground);
            playMode->draw(*window);
            break;
        case MENUTYPE::ABOUT:
            window->draw(aboutBackground);
            about->draw(*window);
            break;
        case MENUTYPE::HIGHSCORES:
            window->draw(highBackground);
            highScore->draw(*window);
            break;
        case MENUTYPE::OPTIONS:
            window->draw(optionsBackground);
            options->draw(*window);
            break;
        case MENUTYPE::JOINLOBBY:
			window->draw(joinBackground);
			joinLobby->draw(*window);
			break;
        case MENUTYPE::CREATELOBBY:
            window->draw(createBackground);
			createLobby->draw(*window);
            testText.draw(*window);
			break;
        }
    } else if (curGameState == GAMESTATE::INGAME) {
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
    }


	// Display what has been drawn
	window->display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return *window;
}
