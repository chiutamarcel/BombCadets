#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Menu.h"
#include "Button.h"

#define MAX_PLAY_MODE 2

class PlayMode : public Menu
{
	vector<Button*>btns;
public:
	PlayMode(float width, float height);

	virtual void draw(RenderWindow* window) override;

	virtual void left() override;

	virtual void right() override;

	virtual void up() override {};
	virtual void down() override {};
	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override;

	virtual int buttonPressed();

	~PlayMode();

private:
	int PlayModeSelected = 0;
	Font font;
	RectangleShape playBackground;
	Texture play_texture;
};

