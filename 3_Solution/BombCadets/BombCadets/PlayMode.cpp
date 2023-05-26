#include "PlayMode.h"
#include "UIProcessing.h"

using namespace std;
using namespace sf;

PlayMode::PlayMode(float width, float height) : Menu()
{
	//Play bacc
	playBackground.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
	play_texture.loadFromFile("Textures\\afterplay.png");
	playBackground.setTexture(&play_texture);

	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}
	btns.push_back(new Button("Singleplayer", font, Color::Red, 70, 132, 0));
	//btn.setCallBack()

	btns.push_back(new Button("Multiplayer", font, Color::Magenta, 70, 832, 0));
	//btn.setCallBack()
};

void PlayMode::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}

	window->draw(playBackground);

	for (auto i = 0; i < btns.size(); i++) {
			btns[i]->draw(window);
	}
};

void PlayMode::left()
{
	btns[PlayModeSelected]->setFillColor(Color::Magenta);

	PlayModeSelected = (PlayModeSelected - 1 + MAX_PLAY_MODE) % MAX_PLAY_MODE;

	btns[PlayModeSelected]->setFillColor(Color::Red);
};

void PlayMode::right()
{
	btns[PlayModeSelected]->setFillColor(Color::Magenta);

	PlayModeSelected = (PlayModeSelected + 1) % MAX_PLAY_MODE;

	btns[PlayModeSelected]->setFillColor(Color::Red);
};

void PlayMode::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType)
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

        if (event.type == Event::KeyPressed) {
            cout << buttonPressed();
            if (event.key.code == Keyboard::Left) {
                left();
                return;
            }

            if (event.key.code == Keyboard::Right) {
                right();
                return;
            }

            if (event.key.code == Keyboard::Return) {

                int y = buttonPressed();

                if (y == 1)
                {
                    UIProcessing::get().switchMenu(MENUTYPE::CREATELOBBY);
                    //create lobby
                    /*createLobb = TextBox(50, sf::Color::White, true);
                    createPass = TextBox(50, sf::Color::White, true);
                    createLobb.setFont();
                    createLobb.setPosition({ 110, 280 });
                    createPass.setFont();
                    createPass.setPosition({ 130, 630 });*/
                    return;
                }

                if (y == 0)
                {
                    UIProcessing::get().switchMenu(MENUTYPE::JOINLOBBY);
                    //join lobby
                    //curUI = new JoinLobby(WINDOWXSIZE, WINDOWYSIZE);
                    ///*joinLobb = TextBox(25, sf::Color::White, true);
                    //joinLobb.setFont();
                    //joinLobb.setPosition({ 820, 85 });*/
                    //curMenu = MENUTYPE::JOINLOBBY;

                    //music.stop();
                    //if (!gameMusic.openFromFile("Media\\game.wav"))
                    //    exit(1); // eroare
                    //gameMusic.play();
                    //gameMusic.setLoop(true);
                    //gameMusic.setVolume(50.f);

                    Game::startSinglePlayer();
                    curGameState = GAMESTATE::INGAME;
                    return;
                }
            }
        }
}

int PlayMode::buttonPressed() {
	return PlayModeSelected;
}

PlayMode::~PlayMode() {};

