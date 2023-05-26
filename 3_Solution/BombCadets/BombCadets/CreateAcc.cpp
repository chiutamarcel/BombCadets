#include "CreateAcc.h"

CreateAcc::CreateAcc(float width, float height) : Menu()
{
	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}
}

int CreateAcc::buttonPressed()
{
	return createAccSelected;
}
