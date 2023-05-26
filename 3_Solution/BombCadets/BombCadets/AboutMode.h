#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Menu.h"
#include "Button.h"

using namespace std;
using namespace sf;

#define MAX_ABOUT 2

class AboutMode : public Menu
{
	vector<Button*>btns;
public:
	AboutMode(float width, float height);

	virtual void draw(RenderWindow* window) override;

	virtual void up() override;

	virtual void down() override;

	virtual void left() override {}
	virtual void right() override {}
	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override;

	virtual int buttonPressed() override;

	~AboutMode() {};

private:
	int AboutSelected = 0;
	Font font;
	RectangleShape aboutBackground;
	Texture about_texture;
	RectangleShape howToPlay;
	Texture howTo_texture;
	RectangleShape controlsBacc;
	Texture	controls_texture;
	Text how;
	Text ctrl;
};

