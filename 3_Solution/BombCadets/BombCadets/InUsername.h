#pragma once
#include "Menu.h"

#include <iostream>
#include "SFML/Graphics.hpp"


using namespace sf;
using namespace std;

class InUsername : public Menu
{
public:
	InUsername(float width, float height);

	virtual void draw(RenderWindow* window) override;

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}

	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override;

	virtual int buttonPressed() override;

	~InUsername() {};

	string username;
private:
	int loginSelected = 0;
	sf::Font font;
	sf::RectangleShape inUsernameBackground;
	sf::Texture inUsername_texture;
	TextBox userTextBox;
};