#include "GameConfig.h"
#include "Map.h"
#include "Entities.h"

#include <vector>
#include <time.h>

using namespace GameConfig;

namespace Map {
	std::vector<std::pair<int, int>> spawnPoints;
	
	int maxPlayers = 2;
	int curPlayers = 0;
}


void Map::spawnCharacter()
{
	if (curPlayers >= maxPlayers)
		return;

	int x = spawnPoints[curPlayers].second;
	int y = spawnPoints[curPlayers].first;

	Entities::getInstance().getCharacters().push_back
	(
		new Character
		(
			sf::Vector2f(x * ENTITYSIZE, y * ENTITYSIZE), PLAYERSIZE, sf::Color::Blue, PLAYERSPEED
		)
	);
	curPlayers++;
}

void Map::addSpawnPoint(int x, int y)
{
	spawnPoints.push_back(std::make_pair(x, y));
}

void Map::readFromFile(std::string filename)
{
	std::ifstream map(filename);

	char** mapMatrix = new char* [(int)(BLOCKSONSCREENY)];
	for (int i = 0; i < (int)(BLOCKSONSCREENY); i++)
	{
		mapMatrix[i] = new char[(int)(BLOCKSONSCREENX) + 1];
	}

	for (int i = 0; i < BLOCKSONSCREENY; i++) {
		for (int j = 0; j < BLOCKSONSCREENX + 1; j++) {
			map.get(mapMatrix[i][j]);
		}
	}
	map.close();

	readFromString(mapMatrix);

	for (int i = 0; i < (int)(BLOCKSONSCREENY); i++)
	{
		delete[] mapMatrix[i];
	}
	delete[] mapMatrix;
}

void stringToEntities(char** mapMatrix) {
	int count = 0;
	// generate the map
	for (int i = 0; i < BLOCKSONSCREENY; i++, std::cout << std::endl)
		for (int j = 0; j < BLOCKSONSCREENX; j++)
		{
			std::cout << mapMatrix [i][j];
			switch (mapMatrix[i][j])
			{
			case '1':
				//create a wall
				Entities::getInstance().getWalls().push_back(new Block(sf::Vector2f(j * ENTITYSIZE, i * ENTITYSIZE), ENTITYSIZE, sf::Color::Green));
				break;
			case '2':
				//create brakable block
				Entities::getInstance().getBreakableBlocks().push_back(new BreakableBlock(sf::Vector2f(j * ENTITYSIZE, i * ENTITYSIZE), ENTITYSIZE, sf::Color::Red));
				break;
			case '3':
				// add spawnpoint
				Map::addSpawnPoint(i, j);
				break;
			case '4':
				//generate AI
				break;
			case 'z':
				//generate menu
				break;
			default:
				break;
			}

			count++;
		}
	std::cout << std::endl;
}

void writeBreakableBlocks(char** mapMatrix) {
	int count = 0;
	std::vector<std::pair<int, int>> emptySpace;

	for (int i = 0; i < BLOCKSONSCREENY; i++)
		for (int j = 0; j < BLOCKSONSCREENX; j++)
		{
			if (mapMatrix[i][j] == '0')
				emptySpace.push_back(std::make_pair(i, j));
			count++;
		}

	int numberOfBreakableWalls = NRBREAKABLEWALLS;
	while (numberOfBreakableWalls)
	{
		srand(time(NULL));
		int index = rand() % emptySpace.size();
		mapMatrix[emptySpace[index].first][emptySpace[index].second] = '2';
		emptySpace.erase(emptySpace.begin() + index);
		numberOfBreakableWalls--;
	}
}

void Map::readFromString(char **mapMatrix)
{	
	writeBreakableBlocks(mapMatrix);
	stringToEntities(mapMatrix);
}
