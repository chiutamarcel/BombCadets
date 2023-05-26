#include "CreateLobby.h"

CreateLobby::CreateLobby(float width, float height) : PlayMode(width, height)
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
}

void CreateLobby::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}
	window->draw(createBackground);
	ip_add.draw(window);
}

void CreateLobby::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType)
{
	if (event.type == sf::Event::TextEntered && ip_add.getSelection() == true)
	{
		ip_add.char_entered(event);
	}

	if (ip_add.getSelection() == false)
	{
		//baga tare aici mihai
	}
}

int CreateLobby::buttonPressed()
{
	return createSelected;
}


