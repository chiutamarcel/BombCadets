#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#define MAX_MAIN_MENU 5

class MainMenu
{
public:
	MainMenu(float width, float height);

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() {
		return MainMenuSelected;
	}

	~MainMenu();

private:
	int MainMenuSelected = 0;
	Font font;
	Text mainMenu[MAX_MAIN_MENU];

};

