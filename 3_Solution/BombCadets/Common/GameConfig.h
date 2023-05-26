#pragma once

enum class GAMESTATE { LOGIN, MAINMENU, INGAME };
enum class MENUTYPE { MAINMENU, PLAY, OPTIONS, HIGHSCORES, ABOUT, JOINLOBBY, CREATELOBBY };
enum class ENTRYTYPE { CHOOSE, IN };

namespace GameConfig {

	const float ENTITYSIZE = 64.0f;
	const float PLAYERSIZE = 64.0f;
	const float PLAYERSPEED = 100.0f;
	const int WINDOWXSIZE = 1344;
	const int WINDOWYSIZE = 832;
	const int NRBREAKABLEWALLS = 75;
	const int BLOCKSONSCREENX = (int) (WINDOWXSIZE / ENTITYSIZE);
	const int BLOCKSONSCREENY = (int) (WINDOWYSIZE / ENTITYSIZE);
	const char mapFile[] = "../map.txt";

}