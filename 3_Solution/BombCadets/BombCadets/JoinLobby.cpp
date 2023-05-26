#include "JoinLobby.h"

JoinLobby::JoinLobby(float width, float height) : PlayMode (width, height)
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
}

void JoinLobby::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}
	window->draw(joinBackground);
	joinLobb.draw(window);
}

void JoinLobby::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType)
{
	if (event.type == sf::Event::TextEntered && joinLobb.getSelection() == true && curMenu == MENUTYPE::JOINLOBBY)
	{
		joinLobb.char_entered(event);
	}
}

int JoinLobby::buttonPressed()
{
	return joinSelected;
}
