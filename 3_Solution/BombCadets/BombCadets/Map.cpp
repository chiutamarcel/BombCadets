#include "GameConfig.h"
#include "Map.h"
#include "Entities.h"

#include <vector>
#include <time.h>

#include "Player.h"
#include "MapText.h"
#include "NPC.h"
#include "Logger.h"

static sf::Texture* wallTexture = new sf::Texture();
static sf::Texture* playerTexture = new sf::Texture();
static sf::Texture* breakableTexture = new sf::Texture();

void init()
{
	wallTexture->loadFromFile("Textures\\breakk.png");
	playerTexture->loadFromFile("Textures\\aidonow.png");
	breakableTexture->loadFromFile("Textures\\actually_breakk.png");
}

using namespace GameConfig;

namespace Map {
	std::vector<std::pair<int, int>> spawnPoints;
	
	int maxPlayers = 2;
	int curPlayers = 0;
} 


void Map::spawnCharacter(CharacterType type)
{
	init();
	if (curPlayers >= maxPlayers)
		return;

	int x = spawnPoints[curPlayers].second;
	int y = spawnPoints[curPlayers].first;

	switch (type) {
	case CharacterType::PLAYER:
		Entities::getInstance().getCharacters().push_back
		(
			new Player
			(
				sf::Vector2f(x * ENTITYSIZE, y * ENTITYSIZE), PLAYERSIZE - 5, playerTexture, PLAYERSPEED
			)
		);
		break;
	case CharacterType::BASE:
		Entities::getInstance().getCharacters().push_back
		(
			new Character
			(
				sf::Vector2f(x * ENTITYSIZE, y * ENTITYSIZE), PLAYERSIZE - 5, playerTexture, PLAYERSPEED
			)
		);
		break;
	case CharacterType::BOT:
		Entities::getInstance().getCharacters().push_back
		(
			new NPC(sf::Vector2f(x * ENTITYSIZE + 4, y * ENTITYSIZE + 4), PLAYERSIZE, sf::Color::Cyan, PLAYERSPEED)
		);
		break;
	}


	curPlayers++;
}

void Map::addSpawnPoint(int x, int y)
{
	spawnPoints.push_back(std::make_pair(x, y));
}

void Map::spawnMapFromFile(std::string filename)
{
	MapText mapText(BLOCKSONSCREENX,BLOCKSONSCREENY);
	mapText.readFromFile(filename);
	std::cout << mapText << std::endl;
	spawnMap(mapText);
}

void stringToEntities(char** mapMatrix) {
	int count = 0;
	// generate the map
	init();
	for (int i = 0; i < BLOCKSONSCREENY; i++, std::cout << std::endl)
		for (int j = 0; j < BLOCKSONSCREENX; j++)
		{
			std::cout << mapMatrix [i][j];
			switch (mapMatrix[i][j])
			{
			case '1':
				//create a wall
				Entities::getInstance().getWalls().push_back(new Block(sf::Vector2f(j * ENTITYSIZE, i * ENTITYSIZE), ENTITYSIZE, wallTexture));
				break;
			case '2':
				//create brakable block
				Entities::getInstance().getBreakableBlocks().push_back(new BreakableBlock(sf::Vector2f(j * ENTITYSIZE, i * ENTITYSIZE), ENTITYSIZE, breakableTexture));
				break;
			case '3':
				// add spawnpoint
				Map::addSpawnPoint(i, j);
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

void Map::spawnMap(MapText mapText)
{	
	//writeBreakableBlocks(mapText);
	Logger::getInstance()->log(LogLevel::INFO, "Generating map...");
	stringToEntities(mapText.c_str());
}
