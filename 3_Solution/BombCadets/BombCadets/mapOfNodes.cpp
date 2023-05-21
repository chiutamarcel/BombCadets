#include "mapOfNodes.h"
#include "Entities.h"
#include "GameConfig.h"

mapOfNodes::mapOfNodes()
{
	entityNodes = new EntityNode * [11];
	for (int y = 0; y <11; y++)
	{
		entityNodes[y] = new EntityNode[21];
		for (int x = 0; x < 21; x++)
		{
			entityNodes[y][x].setPosition(x * GameConfig::ENTITYSIZE + 32, y * GameConfig::ENTITYSIZE + 32);
			entityNodes[y][x].setType(EntityType::PATH);
		}
	}
	
	for (auto it : Entities::getInstance().getWalls())
	{
		int y = it->getShape().getPosition().y / GameConfig::ENTITYSIZE - 2;
		int x = it->getShape().getPosition().x / GameConfig::ENTITYSIZE;
		entityNodes[y][x].setType(EntityType::UNBREAKABLE_WALL);
	}
}

mapOfNodes::~mapOfNodes()
{
	for (int i = 0; i < 11; i++)
	{
		delete[] entityNodes[i];
	}
	delete[] entityNodes;
}

void mapOfNodes::updateMapOfNodes()
{
	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			if (entityNodes[y][x].getType() != EntityType::UNBREAKABLE_WALL)
				entityNodes[y][x].setType(EntityType::PATH);
		}
	}
	
	for (auto it : Entities::getInstance().getCharacters())
	{
		int y = it->getShape().getPosition().y / GameConfig::ENTITYSIZE - 2;
		int x = it->getShape().getPosition().x / GameConfig::ENTITYSIZE;
		entityNodes[y][x].setType(EntityType::CHARACTER);
	}

	for (auto it : Entities::getInstance().getBreakableBlocks())
	{
		int y = it->getShape().getPosition().y / GameConfig::ENTITYSIZE - 2;
		int x = it->getShape().getPosition().x / GameConfig::ENTITYSIZE;
		entityNodes[y][x].setType(EntityType::BREAKABLE_WALL);
	}
	
	setupRelationships();
}

void mapOfNodes::setupRelationships()
{
	/*
	for (int y = 1; y < 10; y++)
	{
		for (int x = 1; x < 20; x++)
		{
			if (entityNodes[y][x].getType() != EntityType::UNBREAKABLE_WALL)
			{
				for (int i = -1; i < 2; i++)
				{
					newY = y + i;
					for (int j = -1; j < 2; j++)
					{
						newX = x + j;
						if (newY > 0 && newY < 10 && newX > 0 && newX < 20 && abs(newX) != abs(newY))
						{
							child = &(entityNodes[newY][newX]);
							if ((newY != y || newX != x) && child->getType() != EntityType::UNBREAKABLE_WALL)
								entityNodes[y][x].addChild(child, 64);
						}
					}
				}
			}
		}
	}
	*/
	for (int y = 1; y < 10; y++)
	{
		for (int x = 1; x < 20; x++)
		{
			if (entityNodes[y][x].getType() != EntityType::BREAKABLE_WALL && entityNodes[y][x].getType() != EntityType::UNBREAKABLE_WALL)
			{
				mapOfNodes::addChild(y, x, y - 1, x);

				mapOfNodes::addChild(y, x, y + 1, x);

				mapOfNodes::addChild(y, x, y, x - 1);

				mapOfNodes::addChild(y, x, y, x + 1);
			}
		}
	}
}

void mapOfNodes::setStart(int y, int x)
{
	pathGenerator.setStart(entityNodes[y][x]);
}

void mapOfNodes::setGoal()
{
	int yGoal = 0, xGoal = 0;
	float distance = 1000000;
	for(int y = 0; y < 11; y++)
		for (int x = 0; x < 21; x++)
		{
			if (entityNodes[y][x].getType() == EntityType::CHARACTER )
			{
				float newDistance = entityNodes[y][x].distanceTo(pathGenerator.getStart());
				if (newDistance < distance && newDistance > 128)
				{
					distance = newDistance;
					yGoal = y;
					xGoal = x;
				}
			}
		}
	pathGenerator.setGoal(entityNodes[yGoal][xGoal]);
}

int mapOfNodes::findPath()
{
	return pathGenerator.findPath<AStar>(path);
}

void mapOfNodes::setSecondaryGoal()
{
	//int yGoal, xGoal;
	//float distance = 1000000;
	//for (int y = 0; y < 11; y++)
	//	for (int x = 0; x < 21; x++)
	//	{
	//		if (entityNodes[y][x].getType() == EntityType::BREAKABLE_WALL)
	//		{
	//			float newDistance = entityNodes[y][x].distanceTo(pathGenerator.getStart());
	//			if (newDistance < distance)
	//			{
	//				distance = newDistance;
	//				yGoal = y;
	//				xGoal = x;
	//			}
	//		}
	//	}
	//pathGenerator.setGoal(entityNodes[yGoal][xGoal]);
	pathGenerator.setGoal(entityNodes[7][17]);
}

void mapOfNodes::setPathToRunFromBomb()
{
	pathGenerator.setStart(*(pathGenerator.getGoal()));
	int yGoal, xGoal;
	float distance = 1000000;
	
	for (int y = 0; y < 11; y++)
		for (int x = 0; x < 21; x++)
		{
			if (entityNodes[y][x].getType() == EntityType::PATH)
			{
				distance = entityNodes[y][x].distanceTo(pathGenerator.getStart());
				if (distance > 128)
				{
					yGoal = y;
					xGoal = x;
					pathGenerator.setGoal(entityNodes[yGoal][xGoal]);
					if (pathGenerator.findPath<AStar>(path) == 1)
						return;					
				}
			}
		}
}

float mapOfNodes::distanceToGoal()
{
	return pathGenerator.getStart()->distanceTo((pathGenerator.getGoal()));
}

EntityNode* mapOfNodes::getGoal()
{
	return pathGenerator.getGoal();
}

std::vector<EntityNode*> mapOfNodes::getPath()
{
	return path;
}

void mapOfNodes::addChild(int y, int x, int newY, int newX)
{

	EntityNode* child;
	if (entityNodes[newY][newX].getType() != EntityType::BREAKABLE_WALL && entityNodes[newY][newX].getType() != EntityType::UNBREAKABLE_WALL)
	{
		child = &(entityNodes[newY][newX]);
		entityNodes[y][x].addChild(child, 54);
	}
}