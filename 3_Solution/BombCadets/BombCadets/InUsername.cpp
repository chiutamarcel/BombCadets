#include "InUsername.h"
#include "UIProcessing.h"

InUsername::InUsername(float width, float height) : Menu()
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
}

void InUsername::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}

	window->draw(inUsernameBackground);
	userTextBox.draw(window);
}

void InUsername::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType)
{
	//if (curGameState == GAMESTATE::LOGIN && curEntryType == ENTRYTYPE::IN) //&& userTextBox.getSelection() == false)
	//{
	//	curGameState = GAMESTATE::MAINMENU;
	//	event.key.code = Keyboard::Escape;
	//	UIProcessing::get().switchMenu(curMenu);
	//}

	if (event.type == sf::Event::TextEntered)
	{
		if (userTextBox.getSelection() == true)
		{
			userTextBox.char_entered(event);
		}
		username = userTextBox.getText();
		//event.key.code = Keyboard::Escape;

	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Return)
		{
			curGameState = GAMESTATE::MAINMENU;
			UIProcessing::get().switchMenu(curMenu);
			return;
		}
	}
}

int InUsername::buttonPressed()
{
	return loginSelected;
}
