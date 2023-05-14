#pragma once

#include <string>
#include <vector>

namespace Map
{
	extern std::vector<std::pair<int, int>> spawnPoints;

	extern int curPlayers;
	extern int maxPlayers;

	void spawnCharacter();
	void addSpawnPoint(int x, int y);

	void readFromFile(std::string filename);
	void readFromString(char** mapMatrix);
};

