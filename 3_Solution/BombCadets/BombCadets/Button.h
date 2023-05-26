#pragma once
#include "UIElement.h"
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class Button : public UIElement
{
	Text button;
	string name;
	Font font;
	Color color;
	int size;
	int xPos;
	int yPos;
public:
	Button(string _name, Font _font, Color _color, int _size, int _xPos, int _yPos);

	virtual void draw(RenderWindow* window) override;
	void setFillColor(Color color);
	Text getButton();
	void setCallback();
	void click();
};

