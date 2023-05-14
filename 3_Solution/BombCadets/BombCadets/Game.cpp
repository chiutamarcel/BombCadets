#include "Game.h"
#include "Map.h"
#include "Client.h"
#include "GameConfig.h"
#include <utility>
#include <fstream>

using namespace GameConfig;

enum class GAMESTATE { MAINMENU, INGAME };
enum class MENUTYPE { MAINMENU, PLAY, OPTIONS, HIGHSCORES, ABOUT };
MENUTYPE curMenu;
GAMESTATE curGameState;

Game::Game() {
    mapFileName = "map.txt";
}

void Game::pollEvents()
{
    // Process events
    sf::Event event;
    while (window->pollEvent(event))
    {
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
                        playMode->MoveLeft();
                        break;
                    }

                    if (event.key.code == Keyboard::Right) {
                        playMode->MoveRight();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int y = playMode->PlayModePressed();

                        if (y == 0)
                        {
                            //single player
                            startSinglePlayer();
                            return;
                        }

                        if (y == 1)
                        {
                            //multi player
                            startMultiPlayer();
                            return;
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
                        about->MoveUp();
                        break;
                    }

                    if (event.key.code == Keyboard::Down) {
                        about->MoveDown();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int y = about->AboutPressed();

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
                        highScore->MoveUp();
                        break;
                    }

                    if (event.key.code == Keyboard::Down) {
                        highScore->MoveDown();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int y = highScore->HighPressed();

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
                        options->MoveUp();
                        break;
                    }

                    if (event.key.code == Keyboard::Down) {
                        options->MoveDown();
                        break;
                    }

                    if (event.key.code == Keyboard::Return) {

                        int y = options->OptionsPressed();

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
    window = new sf::RenderWindow(VideoMode(WINDOWXSIZE, WINDOWYSIZE), "Main Menu");
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
    Map::readFromFile(mapFileName);
    Map::spawnCharacter(Map::CharacterType::PLAYER);
}

void Game::startMultiPlayer() {
    curGameState = GAMESTATE::INGAME;
    Client::getInstance().start();

    // TODO: change later after adding a proper Bot class
    for (int i = 0; i < Map::maxPlayers; i++)
        Map::spawnCharacter(Map::CharacterType::BASE); 
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
