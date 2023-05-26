#pragma once
#include "PlayMode.h"

class JoinLobby : public PlayMode
{
public:
	JoinLobby(float width, float height) : PlayMode(width, height)
	{
		//join bacc
		joinBackground.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
		join_texture.loadFromFile("Textures\\joinLobby.png");
		joinBackground.setTexture(&join_texture);

		joinLobb = TextBox(25, sf::Color::White, true);
		joinLobb.setFont();
		joinLobb.setPosition({ 820, 85 });

		if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
			cout << "No font available\n";
			exit(1);
		}
	};

	virtual void draw(RenderWindow* window) override 
	{
		if (window == nullptr) {
			exit(1);
		}
		window->draw(joinBackground);
		joinLobb.draw(window);
	}

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}
	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override
	{
		if (event.type == sf::Event::TextEntered && joinLobb.getSelection() == true && curMenu == MENUTYPE::JOINLOBBY)
		{
			joinLobb.typedOn(event);
		}
	}

	virtual int buttonPressed() override {
		return joinSelected;
	}

	~JoinLobby() {};

private:
	int joinSelected = 0;
	sf::Font font;
	sf::RectangleShape joinBackground;
	sf::Texture join_texture;
	TextBox joinLobb;
};

