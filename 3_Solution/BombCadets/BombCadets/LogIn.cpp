#include "LogIn.h"

LogIn::LogIn(float width, float height) : Menu()
{
	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}
}

int LogIn::buttonPressed()
{
	return loginSelected;
}
