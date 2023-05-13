#include "Game.h"

#define PLAYERSIZE 50.0f
#define PLAYERSPEED 100.0f

#define WIDTH 1344
#define HEIGTH 832

#define NOMENU -1

enum MENUTYPE { MAINMENU, PLAY, OPTIONS, HIGHSCORES, ABOUT };
int curMenu = MAINMENU;

void Game::pollEvents()
{
    // Process events
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (curMenu) {
        case MAINMENU:
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
                        playMode = new PlayMode(WIDTH, HEIGTH);
                        curMenu = PLAY;
                        break;
                    case 1:
                        options = new Options(WIDTH, HEIGTH);
                        curMenu = OPTIONS;
                        break;
                    case 2:
                        highScore = new HighScore(WIDTH, HEIGTH);
                        curMenu = HIGHSCORES;
                        break;
                    case 3:
                        about = new AboutMode(WIDTH, HEIGTH);
                        curMenu = ABOUT;
                        break;
                    case 4:
                        exit(0);
                        break;
                    }
                }
            }
            break;
        case PLAY:
            if (event.type == Event::Closed) {
                curMenu = MAINMENU;
                delete playMode;
                break;
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    curMenu = MAINMENU;
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
                    }

                    if (y == 1)
                    {
                        //multi player
                    }
                }
            }
            break;

        case ABOUT:

            if (event.type == Event::Closed) {
                curMenu = MAINMENU;
                break;
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    curMenu = MAINMENU;
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
        case HIGHSCORES:

            if (event.type == Event::Closed) {
                curMenu = MAINMENU;
                break;
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    curMenu = MAINMENU;
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
        case OPTIONS:

            if (event.type == Event::Closed) {
                curMenu = MAINMENU;
                break;
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    curMenu = MAINMENU;
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
                curMenu = MAINMENU;
                break;
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    curMenu = MAINMENU;
                    break;
                }
            }

            break;

        }
    }
}
Game::Game() : 
	character(sf::Vector2f(0.0f, 0.0f), PLAYERSIZE, sf::Color::Blue, PLAYERSPEED)
{
	window = nullptr;
}

Game::~Game()
{
	if (window != nullptr)
		delete window;
}

void Game::start()
{

	// Make Main window
    window = new sf::RenderWindow(VideoMode(WIDTH, HEIGTH), "Main Menu");
	mainMenu = new MainMenu(WIDTH, HEIGTH);

	//set background
	background.setSize(Vector2f(WIDTH, HEIGTH));
	Maintexture.loadFromFile("Textures\\mainbackground.png");
	background.setTexture(&Maintexture);

	//Play bacc
	playBackground.setSize(Vector2f(WIDTH, HEIGTH));
	play_texture.loadFromFile("Textures\\afterplay.png");
	playBackground.setTexture(&play_texture);

	//About bacc
	aboutBackground.setSize(Vector2f(WIDTH, HEIGTH));
	about_texture.loadFromFile("Textures\\about.png");
	aboutBackground.setTexture(&about_texture);

    //highscores bacc
    highBackground.setSize(Vector2f(WIDTH, HEIGTH));
    high_texture.loadFromFile("Textures\\highsc.png");
    highBackground.setTexture(&high_texture);

    //options bacc
    optionsBackground.setSize(Vector2f(WIDTH, HEIGTH));
    options_texture.loadFromFile("Textures\\optionen.png");
    optionsBackground.setTexture(&options_texture);
}

void Game::update()
{
    if (curMenu == NOMENU) {
        character.update(deltaTime.asSeconds());
    }

	deltaTime = deltaClock.restart();
}

void Game::draw()
{
	// Clear screen
	window->clear();

	// Draw
    switch (curMenu) {
    case MAINMENU:
        window->draw(background);
        mainMenu->draw(*window);
        break;
    case PLAY:
        window->draw(playBackground);
        playMode->draw(*window);
        break;
    case ABOUT:
        window->draw(aboutBackground);
        about->draw(*window);
        break;
    case HIGHSCORES:
        window->draw(highBackground);
        highScore->draw(*window);
        break;
    case OPTIONS:
        window->draw(optionsBackground);
        options->draw(*window);
        break;
    }

    if (curMenu == NOMENU) {
        window->draw(character.getShape());
    }

	// Display what has been drawn
	window->display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return *window;
}
