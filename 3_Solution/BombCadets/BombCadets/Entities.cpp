#include "Entities.h"

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

