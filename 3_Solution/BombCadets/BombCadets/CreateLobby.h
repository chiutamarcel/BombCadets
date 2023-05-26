#pragma once
#include "PlayMode.h"
#include "Game.h"

class CreateLobby : public PlayMode
{
public:
	CreateLobby(float width, float height);

	virtual void draw(RenderWindow* window) override;

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}
	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override;

	virtual int buttonPressed() override;

	~CreateLobby() {};

private:
	int createSelected = 0;
	sf::Font font;
	sf::RectangleShape createBackground;
	sf::Texture create_texture;
	TextBox ip_add;

	sf::Music music;
	sf::Music gameMusic;

	sf::SoundBuffer buffer;
	sf::Sound sound;
};

