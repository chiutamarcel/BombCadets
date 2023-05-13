#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#define MAX_HIGHSCORE 2

class HighScore
{
public:
	HighScore(float width, float height);

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int HighPressed() {
		return HighSelected;
	}

	~HighScore();

private:
	int HighSelected = 0;
	Font font;
	Text high[MAX_HIGHSCORE];
};

