#pragma once
#include "PlayMode.h"

class JoinLobby : public PlayMode
{
public:
	JoinLobby(float width, float height);

	virtual void draw(RenderWindow* window) override;

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}
	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override;

	virtual int buttonPressed() override;

	~JoinLobby() {};

private:
	int joinSelected = 0;
	sf::Font font;
	sf::RectangleShape joinBackground;
	sf::Texture join_texture;
	TextBox joinLobb;
};

