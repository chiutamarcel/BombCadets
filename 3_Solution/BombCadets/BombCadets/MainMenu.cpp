#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}

	//Play
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::Red);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 300);

	//Options
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::Magenta);
	mainMenu[1].setString("Options");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(400, 400);

	//High_Scores
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::Magenta);
	mainMenu[2].setString("High Scores");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(400, 500);

	//About
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::Magenta);
	mainMenu[3].setString("About");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(400, 600);

	//Quit
	mainMenu[4].setFont(font);
	mainMenu[4].setFillColor(Color::Magenta);
	mainMenu[4].setString("Quit");
	mainMenu[4].setCharacterSize(70);
	mainMenu[4].setPosition(400, 700);

}
MainMenu::~MainMenu()
{

}

//Draw MainMenu

void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_MAIN_MENU; ++i) {
		window.draw(mainMenu[i]);
	}
}

//MoveUp

void MainMenu::MoveUp()
{
	mainMenu[MainMenuSelected].setFillColor(Color::Magenta);

	MainMenuSelected = (MainMenuSelected - 1 + MAX_MAIN_MENU) % MAX_MAIN_MENU;

	mainMenu[MainMenuSelected].setFillColor(Color::Red);
}

//MoveDown

void MainMenu::MoveDown() {
	mainMenu[MainMenuSelected].setFillColor(Color::Magenta);

	MainMenuSelected = (MainMenuSelected + 1) % MAX_MAIN_MENU;

	mainMenu[MainMenuSelected].setFillColor(Color::Red);
}


