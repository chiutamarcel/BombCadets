#pragma once
#include "Menu.h"
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class CreateAcc : public Menu
{
public:
	CreateAcc(float width, float height);

	virtual void draw(RenderWindow* window) override {}

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}

	virtual int buttonPressed() override;

	~CreateAcc() {};

private:
	int createAccSelected = 0;
	Font font;
};

