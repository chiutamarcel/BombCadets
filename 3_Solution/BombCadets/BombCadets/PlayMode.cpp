#include "PlayMode.h"

PlayMode::PlayMode(float width, float height)
{
	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}

	//Single
	playMode[0].setFont(font);
	playMode[0].setFillColor(Color::Red);
	playMode[0].setString("SinglePlayer");
	playMode[0].setCharacterSize(70);
	playMode[0].setPosition(132, 0);

	//Multi
	playMode[1].setFont(font);
	playMode[1].setFillColor(Color::Magenta);
	playMode[1].setString("MultiPlayer");
	playMode[1].setCharacterSize(70);
	playMode[1].setPosition(832, 0);

}
PlayMode::~PlayMode()
{

}

//Draw PlayMode

void PlayMode::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_PLAY_MODE; ++i) {
		window.draw(playMode[i]);
	}
}

//MoveUp

void PlayMode::MoveLeft()
{
	playMode[PlayModeSelected].setFillColor(Color::Magenta);

	PlayModeSelected = (PlayModeSelected - 1 + MAX_PLAY_MODE) % MAX_PLAY_MODE;

	playMode[PlayModeSelected].setFillColor(Color::Red);
}

//MoveDown

void PlayMode::MoveRight() {
	playMode[PlayModeSelected].setFillColor(Color::Magenta);

	PlayModeSelected = (PlayModeSelected + 1) % MAX_PLAY_MODE;

	playMode[PlayModeSelected].setFillColor(Color::Red);
}


