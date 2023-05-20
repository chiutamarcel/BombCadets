#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Menu.h"

using namespace std;
using namespace sf;

#define MAX_PLAY_MODE 2

class PlayMode : public Menu
{
	// vector<Button*> btns;
public:
	PlayMode(float width, float height) : Menu()
	{
		if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
			cout << "No font available\n";
			exit(1);
		}
		//btns.push_back(new Button(x, y, dimx, dimy, ""))
		//btn.setCallBackFunction()

		//Single
		playMode[0].setFont(font);
		playMode[0].setFillColor(Color::Red);
		playMode[0].setString("Create Lobby");
		playMode[0].setCharacterSize(70);
		playMode[0].setPosition(132, 0);

		//Multi
		playMode[1].setFont(font);
		playMode[1].setFillColor(Color::Magenta);
		playMode[1].setString("Join Lobby");
		playMode[1].setCharacterSize(70);
		playMode[1].setPosition(832, 0);
	};

	virtual void draw(RenderWindow& window) override
	{
		for (int i = 0; i < MAX_PLAY_MODE; ++i) {
			window.draw(playMode[i]);
		}
	};

	virtual void left() override 
	{
		playMode[PlayModeSelected].setFillColor(Color::Magenta);

		PlayModeSelected = (PlayModeSelected - 1 + MAX_PLAY_MODE) % MAX_PLAY_MODE;

		playMode[PlayModeSelected].setFillColor(Color::Red);
	};

	virtual void right() override
	{
		playMode[PlayModeSelected].setFillColor(Color::Magenta);

		PlayModeSelected = (PlayModeSelected + 1) % MAX_PLAY_MODE;

		playMode[PlayModeSelected].setFillColor(Color::Red);
	};

	virtual void up() override {};
	virtual void down() override {};

	virtual int buttonPressed() {
		return PlayModeSelected;
	}

	~PlayMode() {};

private:
	int PlayModeSelected = 0;
	Font font;
	Text playMode[MAX_PLAY_MODE];

};

