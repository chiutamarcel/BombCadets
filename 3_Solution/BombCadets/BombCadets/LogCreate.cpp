#include "LogCreate.h"


LogCreate::LogCreate(float width, float height) : Menu()
{
	if (!font.loadFromFile("Fonts\\SpaceMission.otf")) {
		cout << "No font available\n";
		exit(1);
	}

	btns.push_back(new Button("Create Account", font, Color::Red, 70, 300, 30));
	//btn.setCallBack()

	btns.push_back(new Button("Log In", font, Color::Magenta, 70, 250, 130));
	//btn.setCallBack()
};

void LogCreate::draw(RenderWindow* window)
{
	if (window == nullptr) {
		exit(1);
	}

	for (auto i = 0; i < btns.size(); i++) {
		btns[i]->draw(window);
	}
};

void LogCreate::up()
{
	btns[logCreateSelected]->setFillColor(Color::Magenta);

	logCreateSelected = (logCreateSelected - 1 + MAX_CHOOSE) % MAX_CHOOSE;

	btns[logCreateSelected]->setFillColor(Color::Red);
};

void LogCreate::down()
{
	btns[logCreateSelected]->setFillColor(Color::Magenta);

	logCreateSelected = (logCreateSelected + 1) % MAX_CHOOSE;

	btns[logCreateSelected]->setFillColor(Color::Red);
};

int LogCreate::buttonPressed() {
	return logCreateSelected;
}

LogCreate::~LogCreate() {};