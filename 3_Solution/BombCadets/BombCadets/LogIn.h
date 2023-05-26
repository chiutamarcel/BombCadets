#pragma once
#include "Menu.h"
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class LogIn : public Menu
{
public:
public:
	LogIn(float width, float height) : Menu()
	{
		if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
			cout << "No font available\n";
			exit(1);
		}
	};

	virtual void draw(RenderWindow* window) override {}

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}

	virtual int buttonPressed() override {
		return loginSelected;
	}

	~LogIn() {};

private:
	int loginSelected = 0;
	Font font;
};

