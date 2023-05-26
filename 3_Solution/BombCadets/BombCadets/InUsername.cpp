#include "InUsername.h"
#include "UIProcessing.h"

void InUsername::pollEvents(Event event, MENUTYPE& curMenu, GAMESTATE& curGameState, ENTRYTYPE& curEntryType)
{
	//if (curGameState == GAMESTATE::LOGIN && curEntryType == ENTRYTYPE::IN) //&& userTextBox.getSelection() == false)
	//{
	//	curGameState = GAMESTATE::MAINMENU;
	//	event.key.code = Keyboard::Escape;
	//	UIProcessing::get().switchMenu(curMenu);
	//}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Return)
		{
			curGameState = GAMESTATE::MAINMENU;
			UIProcessing::get().switchMenu(curMenu);
			return;
		}
	}

	if (curEntryType == ENTRYTYPE::IN && userTextBox.getSelection() == true)
	{
		if (event.type == sf::Event::TextEntered)
		{
			userTextBox.typedOn(event);
		}
		//username = userTextBox.getText();
		//event.key.code = Keyboard::Escape;

	}


}
