#pragma once

#include <string>
#include <vector>

#include "MapText.h"

namespace Map
{
	enum class CharacterType {
		BASE,
		PLAYER,
		BOT
	};

	extern std::vector<std::pair<int, int>> spawnPoints;

	extern int curPlayers;
	extern int maxPlayers;

	void spawnCharacter(CharacterType type);
	void addSpawnPoint(int x, int y);

	void spawnMapFromFile(std::string filename);
	void spawnMap(MapText mapText);
};

