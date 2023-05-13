#include "Options.h"

Options::Options(float width, float height)
{
	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}

	//Play
	options[0].setFont(font);
	options[0].setFillColor(Color::White);
	options[0].setString("Player skin");
	options[0].setCharacterSize(70);
	options[0].setPosition(200, 200);

	//Options
	options[1].setFont(font);
	options[1].setFillColor(Color::Cyan);
	options[1].setString("Bomb skin");
	options[1].setCharacterSize(70);
	options[1].setPosition(200, 400);

	//High_Scores
	options[2].setFont(font);
	options[2].setFillColor(Color::Cyan);
	options[2].setString("Sound");
	options[2].setCharacterSize(70);
	options[2].setPosition(200, 600);
}
Options::~Options()
{

}

//Draw Options

void Options::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_OPTIONS; ++i) {
		window.draw(options[i]);
	}
}

//MoveUp

void Options::MoveUp()
{
	options[OptionsSelected].setFillColor(Color::Cyan);

	OptionsSelected = (OptionsSelected - 1 + MAX_OPTIONS) % MAX_OPTIONS;

	options[OptionsSelected].setFillColor(Color::White);
}

//MoveDown

void Options::MoveDown() {
	options[OptionsSelected].setFillColor(Color::Cyan);

	OptionsSelected = (OptionsSelected + 1) % MAX_OPTIONS;

	options[OptionsSelected].setFillColor(Color::White);
}