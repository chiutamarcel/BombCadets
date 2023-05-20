#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Menu.h"

using namespace std;
using namespace sf;

#define MAX_OPTIONS 3

class Options : public Menu
{
public:
	Options(float width, float height) : Menu() {
		if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
			cout << "No font available\n";
			exit(1);
		}
		//Sound
		options[0].setFont(font);
		options[0].setFillColor(Color::White);
		options[0].setString("Player Skin");
		options[0].setCharacterSize(70);
		options[0].setPosition(200, 250);
		//Music
		options[1].setFont(font);
		options[1].setFillColor(Color::Cyan);
		options[1].setString("Bomb Skin");
		options[1].setCharacterSize(70);
		options[1].setPosition(200, 400);
		//Back
		options[2].setFont(font);
		options[2].setFillColor(Color::Cyan);
		options[2].setString("Sound");
		options[2].setCharacterSize(70);
		options[2].setPosition(200, 550);
	};

	virtual void draw(RenderWindow& window) override
	{
		for (int i = 0; i < MAX_OPTIONS; ++i) {
			window.draw(options[i]);
		}
	};

	virtual void up() override
	{
		options[OptionsSelected].setFillColor(Color::Cyan);

		OptionsSelected = (OptionsSelected - 1 + MAX_OPTIONS) % MAX_OPTIONS;

		options[OptionsSelected].setFillColor(Color::White);
	};
	virtual void down() override
	{
		options[OptionsSelected].setFillColor(Color::Cyan);

		OptionsSelected = (OptionsSelected + 1) % MAX_OPTIONS;

		options[OptionsSelected].setFillColor(Color::White);
	};

	virtual void left() override {};
	virtual void right() override {};

	virtual int buttonPressed() {
		return OptionsSelected;
	}

	~Options() {};

private:
	int OptionsSelected = 0;
	Font font;
	Text options[MAX_OPTIONS];


};

