#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Menu.h"

using namespace std;
using namespace sf;

#define MAX_ABOUT 2

class AboutMode : public Menu
{
public:
	AboutMode(float width, float height) : Menu()
	{
		if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
			cout << "No font available\n";
			exit(1);
		}
		//How to Play
		about[0].setFont(font);
		about[0].setFillColor(Color::Red);
		about[0].setString("How to Play");
		about[0].setCharacterSize(70);
		about[0].setPosition(800, 300);
		//Controls
		about[1].setFont(font);
		about[1].setFillColor(Color::Magenta);
		about[1].setString("Controls");
		about[1].setCharacterSize(70);
		about[1].setPosition(800, 450);	
	};

	virtual void draw(RenderWindow& window) override
	{
		for (int i = 0; i < MAX_ABOUT; ++i) {
			window.draw(about[i]);
		}
	};

	virtual void up() override
	{
		about[AboutSelected].setFillColor(Color::Magenta);

		AboutSelected = (AboutSelected - 1 + MAX_ABOUT) % MAX_ABOUT;

		about[AboutSelected].setFillColor(Color::Red);
	};

	virtual void down() override
	{
		about[AboutSelected].setFillColor(Color::Magenta);

		AboutSelected = (AboutSelected + 1) % MAX_ABOUT;

		about[AboutSelected].setFillColor(Color::Red);
	};

	virtual void left() override {}
	virtual void right() override {}

	virtual int buttonPressed() override{
		return AboutSelected;
	}

	~AboutMode() {};

private:
	int AboutSelected = 0;
	Font font;
	Text about[MAX_ABOUT];

};

