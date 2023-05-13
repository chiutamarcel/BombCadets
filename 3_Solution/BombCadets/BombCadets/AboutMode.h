#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#define MAX_ABOUT 2

class AboutMode
{
public:
	AboutMode(float width, float height);

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int AboutPressed() {
		return AboutSelected;
	}

	~AboutMode();

private:
	int AboutSelected = 0;
	Font font;
	Text about[MAX_ABOUT];

};

