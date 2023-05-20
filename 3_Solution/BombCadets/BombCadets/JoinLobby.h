#pragma once
#include "PlayMode.h"

class JoinLobby : public PlayMode
{
public:
	JoinLobby(float width, float height) : PlayMode(width, height)
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
		return joinSelected;
	}

	~JoinLobby() {};

private:
	int joinSelected = 0;
	Font font;
};

