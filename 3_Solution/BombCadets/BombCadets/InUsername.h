#pragma once
#include "Menu.h"

#include <iostream>
#include "SFML/Graphics.hpp"


using namespace sf;
using namespace std;

class InUsername : public Menu
{
public:
	InUsername(float width, float height) : Menu()
	{
		//inUsername bacc
		inUsernameBackground.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
		inUsername_texture.loadFromFile("Textures\\user_page.png");
		inUsernameBackground.setTexture(&inUsername_texture);

		userTextBox = TextBox(60, sf::Color::Black, true);
		userTextBox.setFont();
		userTextBox.setPosition({ 530, 60 });

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

		window->draw(inUsernameBackground);
		userTextBox.draw(window);
	};

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}

	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override;

	virtual int buttonPressed() override {
		return loginSelected;
	}

	~InUsername() {};

	string getUsername() {
		return username;
	}


private:
	int loginSelected = 0;
	sf::Font font;
	sf::RectangleShape inUsernameBackground;
	sf::Texture inUsername_texture;
	TextBox userTextBox;

	string username;
};