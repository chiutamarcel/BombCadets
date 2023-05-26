#pragma once
#include "Menu.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Button.h"

using namespace std;
using namespace sf;

#define MAX_HIGHSCORE 2

class HighScore: public Menu
{
	vector<Button*> btns;
public:
	HighScore(float width, float height);

	virtual void draw(RenderWindow* window) override;

	virtual void up() override;

	virtual void down()	override;

	virtual void left() override {}
	virtual void right() override {}
	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override;

	virtual int buttonPressed() override;

	~HighScore();

private:
	int HighSelected = 0;
	Font font;
	RectangleShape highBackground;
	Texture high_texture;
};

