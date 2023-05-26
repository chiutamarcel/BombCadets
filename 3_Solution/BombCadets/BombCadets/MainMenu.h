#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Menu.h"
#include "Button.h"

using namespace std;
using namespace sf;

#define MAX_MAIN_MENU 5

class MainMenu : public Menu
{
	vector<Button*>btns;
public:
	MainMenu(float width, float height);

	virtual void draw(RenderWindow* window) override;

	virtual void up() override;
	virtual void down() override;

	virtual void left() override {}
	virtual void right() override {}
	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override;

	virtual int buttonPressed() override ;

	~MainMenu();

private:
	int MainMenuSelected = 0;
	Font font;
	RectangleShape background;
	Texture Maintexture;
};

