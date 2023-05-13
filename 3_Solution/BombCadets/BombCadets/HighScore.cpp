#include "HighScore.h"

HighScore::HighScore(float width, float height)
{
	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}

	//Local
	high[0].setFont(font);
	high[0].setFillColor(Color::Red);
	high[0].setString("Local");
	high[0].setCharacterSize(70);
	high[0].setPosition(600, 600);

	//Regional
	high[1].setFont(font);
	high[1].setFillColor(Color::Magenta);
	high[1].setString("Regional");
	high[1].setCharacterSize(70);
	high[1].setPosition(550, 700);
}
HighScore::~HighScore()
{

}

//Draw HighScore

void HighScore::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_HIGHSCORE; ++i) {
		window.draw(high[i]);
	}
}

//MoveUp

void HighScore::MoveUp()
{
	high[HighSelected].setFillColor(Color::Magenta);

	HighSelected = (HighSelected - 1 + MAX_HIGHSCORE) % MAX_HIGHSCORE;

	high[HighSelected].setFillColor(Color::Red);
}

//MoveDown

void HighScore::MoveDown() {
	high[HighSelected].setFillColor(Color::Magenta);

	HighSelected = (HighSelected + 1) % MAX_HIGHSCORE;

	high[HighSelected].setFillColor(Color::Red);
}