#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#define MAX_OPTIONS 3

class Options
{
public:
	Options(float width, float height);

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int OptionsPressed() {
		return OptionsSelected;
	}

	~Options();

private:
	int OptionsSelected = 0;
	Font font;
	Text options[MAX_OPTIONS];


};

