#pragma once

namespace GameConfig {
	const float ENTITYSIZE = 64.0f;
	const float PLAYERSIZE = 56.0f;
	const float PLAYERSPEED = 100.0f;
	const int WINDOWXSIZE = 1344;
	const int WINDOWYSIZE = 832;
	const int NRBREAKABLEWALLS = 65;
	const int BLOCKSONSCREENX = (int) (WINDOWXSIZE / ENTITYSIZE);
	const int BLOCKSONSCREENY = (int) (WINDOWYSIZE / ENTITYSIZE);
	const char mapFile[] = "../map.txt";
}