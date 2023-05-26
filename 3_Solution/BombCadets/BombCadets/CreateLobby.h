#pragma once
#include "PlayMode.h"
#include "Game.h"

class CreateLobby : public PlayMode
{
public:
	CreateLobby(float width, float height) : PlayMode(width, height)
	{
		//create bacc
		createBackground.setSize(Vector2f(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE));
		create_texture.loadFromFile("Textures\\server_ip.png");
		createBackground.setTexture(&create_texture);

		ip_add = TextBox(75, sf::Color::Black, true);
		ip_add.setFont();
		ip_add.setPosition({ 210, 480 });


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
		window->draw(createBackground);
		ip_add.draw(window);
	};
	

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}
	virtual void pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType) override
	{

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
			std::string text = ip_add.getText();

			std::string ip;
			std::string port_str;

			ip = text.substr(0, text.find(':'));
			port_str = text.substr(text.find(':') + 1, text.size());

			//std::cout << ip << ":" << port << std::endl;

			unsigned short port;
			port = atoi(port_str.c_str());

			Game::startMultiPlayer(ip, port);
		}


		if (event.type == sf::Event::TextEntered && ip_add.getSelection() == true)
		{
			ip_add.typedOn(event);
		}
	}

	virtual int buttonPressed() override {
		return createSelected;
	}

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
