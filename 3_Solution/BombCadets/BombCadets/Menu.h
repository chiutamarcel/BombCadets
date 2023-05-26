#pragma once
#include "UIElement.h"
#include "GameConfig.h"
#include "TextBox.h"

class Menu : public UIElement
{
	
public:
	Menu() {};
	~Menu() {};
	virtual int buttonPressed() = 0;
	virtual void up() = 0;
	virtual void down() = 0;
	virtual void left() = 0;
	virtual void right() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void pollEvents(sf::Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) = 0;
};

