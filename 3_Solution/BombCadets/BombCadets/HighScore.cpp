#include "HighScore.h"
#include "UIProcessing.h"

HighScore::HighScore(float width, float height) : Menu()
{
	//highscores bacc
	highBackground.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
	high_texture.loadFromFile("Textures\\highsc.png");
	highBackground.setTexture(&high_texture);

	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}

	btns.push_back(new Button("Local", font, Color::Red, 70, 600, 600));
	//btn.setCallBack()

	btns.push_back(new Button("Regional", font, Color::Magenta, 70, 550, 700));
	//btn.setCallBack()
};

void HighScore::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}

	window->draw(highBackground);

	for (auto i = 0; i < btns.size(); i++) {
		btns[i]->draw(window);
	}
};

void HighScore::up()
{
	btns[HighSelected]->setFillColor(Color::Magenta);

	HighSelected = (HighSelected - 1 + MAX_HIGHSCORE) % MAX_HIGHSCORE;

	btns[HighSelected]->setFillColor(Color::Red);
};

void HighScore::down()
{
	btns[HighSelected]->setFillColor(Color::Magenta);

	HighSelected = (HighSelected + 1) % MAX_HIGHSCORE;

	btns[HighSelected]->setFillColor(Color::Red);
};

void HighScore::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType)
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
                    //local
                }

                if (y == 1)
                {
                    //regional
                }
            }

        }

}

int HighScore::buttonPressed() {
	return HighSelected;
}

HighScore::~HighScore() {};