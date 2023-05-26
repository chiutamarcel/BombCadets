#include "Entities.h"

#define BOMB_SIZE 32.0f

void Entities::removeCharacter(Character* character)
{
	for (auto it = characters.begin(); it != characters.end(); ++it)
	{
		if (*it == character)
		{
			characters.erase(it);
			break;
		}
	}
}

void Entities::removeBreakableBlock(BreakableBlock* block)
{
	for (auto it = breakableBlocks.begin(); it != breakableBlocks.end(); ++it)
	{
		if (*it == block)
		{
			breakableBlocks.erase(it);
			break;
		}
	}
}

void Entities::removeBomb(Bomb* bomb)
{
	for (auto it = bombs.begin(); it != bombs.end(); ++it)
	{
		if (*it == bomb)
		{
			bombs.erase(it);
			break;
		}
	}
}

void Entities::removeExplosion(Explosion* explosion)
{
	for (auto it = explosions.begin(); it != explosions.end(); ++it)
	{
		if (*it == explosion)
		{
			
			explosions.erase(it);
			
			break;
		}
	}
}

void Entities::setPlayer(Player& _player)
{
	player = &(_player);
}

Player& Entities::getPlayer()
{
	if (player == nullptr)
		throw std::string("Player is null");

	return *player;
}

void Entities::spawnBomb(float x, float y)
{
	spawnBomb(sf::Vector2f(x, y));
}

void Entities::spawnBomb(sf::Vector2f position)
{
	getBombs().push_back(
		new Bomb(position - sf::Vector2f(BOMB_SIZE, BOMB_SIZE) * 0.5f, BOMB_SIZE)
	);
}

Entities::Entities()
{
	player = nullptr;
}

Entities::~Entities()
{
	for (auto wall : walls) {
		delete wall;
	}

	for (auto c : characters) {
		delete c;
	}

	for (auto bBlk : breakableBlocks) {
		delete bBlk;
	}

	for (auto bomb : bombs) {
		delete bomb;
	}

	for (auto explosion : explosions) {
		delete explosion;
	}
}

