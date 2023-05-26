#include "Button.h"

Button::Button(string _name, Font _font, Color _color, int _size, int _xPos, int _yPos) : UIElement()
{
	name = _name;
	font = _font;
	color = _color;
	size = _size;
	xPos = _xPos;
	yPos = _yPos;

	button.setString(name);
	button.setFont(font);
	button.setFillColor(color);
	button.setCharacterSize(size);
	button.setPosition(xPos, yPos);
};

void Button::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}
	window->draw(button);
}

void Button::setFillColor(Color color) { button.setFillColor(color); };
Text Button::getButton() { return button; };
void Button::setCallback() {};
void Button::click() {};
