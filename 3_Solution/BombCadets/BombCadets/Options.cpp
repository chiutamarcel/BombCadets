#include "Options.h"
#include "UIProcessing.h"

Options::Options(float width, float height)
{
	//options bacc
	optionsBackground.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
	options_texture.loadFromFile("Textures\\optionen.png");
	optionsBackground.setTexture(&options_texture);

	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}
	btns.push_back(new Button("Player Skin", font, Color::White, 70, 200, 250));
	//btn.setCallBack()

	btns.push_back(new Button("Bomb Skin", font, Color::Cyan, 70, 200, 400));
	//btn.setCallBack()

	btns.push_back(new Button("Sound", font, Color::Cyan, 70, 200, 550));
	//btn.setCallBack()
};

void Options::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}

	window->draw(optionsBackground);

	for (auto i = 0; i < btns.size(); i++) {
		btns[i]->draw(window);
	}
}

void Options::up()
{
	btns[OptionsSelected]->setFillColor(Color::Cyan);

	OptionsSelected = (OptionsSelected - 1 + MAX_OPTIONS) % MAX_OPTIONS;

	btns[OptionsSelected]->setFillColor(Color::White);
}

void Options::down()
{
	btns[OptionsSelected]->setFillColor(Color::Cyan);

	OptionsSelected = (OptionsSelected + 1) % MAX_OPTIONS;

	btns[OptionsSelected]->setFillColor(Color::White);
}

void Options::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType)
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
}

int Options::buttonPressed()
{
	return OptionsSelected;
}

Options::~Options() {}
