#include "AboutMode.h"
#include "UIProcessing.h"

AboutMode::AboutMode(float width, float height) : Menu()
{
	//About bacc
	aboutBackground.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
	about_texture.loadFromFile("Textures\\about.png");
	aboutBackground.setTexture(&about_texture);

	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}
	btns.push_back(new Button("How to play", font, Color::Red, 70, 800, 300));
	//btn.setCallBack()

	btns.push_back(new Button("Controls", font, Color::Magenta, 70, 800, 450));
	//btn.setCallBack()	
}

void AboutMode::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}

	window->draw(aboutBackground);

	for (auto i = 0; i < btns.size(); i++) {
		btns[i]->draw(window);
	}
}

void AboutMode::up()
{
	btns[AboutSelected]->setFillColor(Color::Magenta);

	AboutSelected = (AboutSelected - 1 + MAX_ABOUT) % MAX_ABOUT;

	btns[AboutSelected]->setFillColor(Color::Red);
}

void AboutMode::down()
{
	btns[AboutSelected]->setFillColor(Color::Magenta);

	AboutSelected = (AboutSelected + 1) % MAX_ABOUT;

	btns[AboutSelected]->setFillColor(Color::Red);
}

void AboutMode::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType)
{
        if (event.type == Event::Closed) {
            UIProcessing::get().switchMenu(MENUTYPE::MAINMENU);
            return;
        }

        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                UIProcessing::get().switchMenu(MENUTYPE::MAINMENU);
                return;
            }
        }

        if (event.type == Event::KeyReleased) {
            if (event.key.code == Keyboard::Up) {
                up();
                return;
            }

            if (event.key.code == Keyboard::Down) {
                down();
                return;
            }

            if (event.key.code == Keyboard::Return) {

                int y = buttonPressed();

                if (y == 0)
                {
                    /*howToPlay.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
                    howTo_texture.loadFromFile("Textures\\htp.png");
                    howToPlay.setTexture(&howTo_texture);

                    window.draw(howToPlay);*/
                }

                if (y == 1)
                {
                    /*controlsBacc.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
                    controls_texture.loadFromFile("Textures\\ctrl.png");
                    controlsBacc.setTexture(&controls_texture);

                    window.draw(controlsBacc);*/
                }
            }

        }
}

int AboutMode::buttonPressed()
{
	return AboutSelected;
}
