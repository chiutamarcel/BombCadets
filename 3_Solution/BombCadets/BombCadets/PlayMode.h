#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#define MAX_PLAY_MODE 2

class PlayMode
{
public:
	PlayMode(float width, float height);

	void draw(RenderWindow& window);
	void MoveLeft();
	void MoveRight();

	int PlayModePressed() {
		return PlayModeSelected;
	}

	~PlayMode();

private:
	int PlayModeSelected = 0;
	Font font;
	Text playMode[MAX_PLAY_MODE];

};

