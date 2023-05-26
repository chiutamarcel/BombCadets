#include "MainMenu.h"
#include "UIProcessing.h"

MainMenu::MainMenu(float width, float height) : Menu()
{
	//set background
	background.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
	Maintexture.loadFromFile("Textures\\mainbackground.png");
	background.setTexture(&Maintexture);

	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}

	btns.push_back(new Button("Play", font, Color::Red, 70, 400, 300));
	//btn.setCallBack()
	/*mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::Red);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 300);*/

	btns.push_back(new Button("Options", font, Color::Magenta, 70, 400, 400));
	//btn.setCallBack()
	//mainMenu[1].setFont(font);
	//mainMenu[1].setFillColor(Color::Magenta);
	//mainMenu[1].setString("Options");
	//mainMenu[1].setCharacterSize(70);
	//mainMenu[1].setPosition(400, 400);

	btns.push_back(new Button("High Scores", font, Color::Magenta, 70, 400, 500));
	//btn.setCallBack()
	//mainMenu[2].setFont(font);
	//mainMenu[2].setFillColor(Color::Magenta);
	//mainMenu[2].setString("High Scores");
	//mainMenu[2].setCharacterSize(70);
	//mainMenu[2].setPosition(400, 500);

	btns.push_back(new Button("About", font, Color::Magenta, 70, 400, 600));
	//btn.setCallBack()
	/*mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::Magenta);
	mainMenu[3].setString("About");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(400, 600);*/

	btns.push_back(new Button("Quit", font, Color::Magenta, 70, 400, 700));
	//btn.setCallBack()
	/*mainMenu[4].setFont(font);
	mainMenu[4].setFillColor(Color::Magenta);
	mainMenu[4].setString("Quit");
	mainMenu[4].setCharacterSize(70);
	mainMenu[4].setPosition(400, 700);*/
};

void MainMenu::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}

	window->draw(background);

	for (auto i = 0; i < btns.size(); i++) {
		btns[i]->draw(window);
	}
};

void MainMenu::up()
{
	btns[MainMenuSelected]->setFillColor(Color::Magenta);

	MainMenuSelected = (MainMenuSelected - 1 + MAX_MAIN_MENU) % MAX_MAIN_MENU;

	btns[MainMenuSelected]->setFillColor(Color::Red);
};
void MainMenu::down()
{
	btns[MainMenuSelected]->setFillColor(Color::Magenta);

	MainMenuSelected = (MainMenuSelected + 1) % MAX_MAIN_MENU;

	btns[MainMenuSelected]->setFillColor(Color::Red);
};

int MainMenu::buttonPressed() {
	return MainMenuSelected;
};

void MainMenu::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) {
	    if (event.type == Event::Closed) {
			exit(0);
        }
        if (event.type == Event::KeyPressed) {

            if (event.key.code == Keyboard::Up) {
                up();
            }

            if (event.key.code == Keyboard::Down) {
                down();
            }

            if (event.key.code == Keyboard::Return) {

                int x = buttonPressed();
                switch (x) {
                case 0:
					UIProcessing::get().switchMenu(MENUTYPE::PLAY);
                    break;
                case 1:
					UIProcessing::get().switchMenu(MENUTYPE::OPTIONS);
                    break;
                case 2:
					UIProcessing::get().switchMenu(MENUTYPE::HIGHSCORES);
                    break;
                case 3:
					UIProcessing::get().switchMenu(MENUTYPE::ABOUT);
                    break;
                case 4:
                    exit(0);
                    break;
                }
            }
        }
}

MainMenu::~MainMenu() {};