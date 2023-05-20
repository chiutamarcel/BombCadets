#pragma once
#include "PlayMode.h"

class CreateLobby : public PlayMode
{
public:
	CreateLobby(float width, float height) : PlayMode(width, height)
	{
		if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
			cout << "No font available\n";
			exit(1);
		}
	};

	virtual void draw(RenderWindow& window) override {}

	virtual void up() override {}

	virtual void down() override {}

	virtual void left() override {}
	virtual void right() override {}

	virtual int buttonPressed() override {
		return createSelected;
	}

	~CreateLobby() {};

private:
	int createSelected = 0;
	Font font;
};

