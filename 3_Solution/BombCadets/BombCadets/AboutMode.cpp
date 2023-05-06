#include "AboutMode.h"

AboutMode::AboutMode(float width, float height)
{
	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}

	//How to Play
	about[0].setFont(font);
	about[0].setFillColor(Color::Red);
	about[0].setString("How to Play");
	about[0].setCharacterSize(70);
	about[0].setPosition(800, 300);

	//Controls
	about[1].setFont(font);
	about[1].setFillColor(Color::Magenta);
	about[1].setString("Controls");
	about[1].setCharacterSize(70);
	about[1].setPosition(800, 450);
}
AboutMode::~AboutMode()
{

}

//Draw AboutMode

void AboutMode::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_ABOUT; ++i) {
		window.draw(about[i]);
	}
}

//MoveUp

void AboutMode::MoveUp()
{
	about[AboutSelected].setFillColor(Color::Magenta);

	AboutSelected = (AboutSelected - 1 + MAX_ABOUT) % MAX_ABOUT;

	about[AboutSelected].setFillColor(Color::Red);
}

//MoveDown

void AboutMode::MoveDown() {
	about[AboutSelected].setFillColor(Color::Magenta);

	AboutSelected = (AboutSelected + 1) % MAX_ABOUT;

	about[AboutSelected].setFillColor(Color::Red);
}


