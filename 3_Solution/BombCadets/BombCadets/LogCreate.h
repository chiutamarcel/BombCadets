#pragma once
#include "Menu.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Button.h"

using namespace std;
using namespace sf;

#define MAX_CHOOSE 2

class LogCreate : public Menu
{
	vector<Button*> btns;
public:
	LogCreate(float width, float height);

	virtual void draw(RenderWindow* window) override;

	virtual void up() override;

	virtual void down()	override;

	virtual void left() override {}
	virtual void right() override {}

	virtual int buttonPressed() override;

	~LogCreate();

private:
	int logCreateSelected = 0;
	Font font;
};

