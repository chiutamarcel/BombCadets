#include "mapOfNodes.h"
#include "Entities.h"
#include "GameConfig.h"

mapOfNodes::mapOfNodes()
{
	entityNodes = new EntityNode * [11];
	for (int i = 0; i <11; i++)
	{
		entityNodes[i] = new EntityNode[21];
		for (int j = 0; j < 21; j++)
		{
			entityNodes[i][j].setPosition(i * GameConfig::ENTITYSIZE + 32, j * GameConfig::ENTITYSIZE + 32);
			entityNodes[i][j].setType(EntityType::PATH);
		}
	}
	
	for (auto i : Entities::getInstance().getWalls())
	{
		int x = i->getShape().getOrigin().x / GameConfig::ENTITYSIZE;
		int y = i->getShape().getOrigin().y / GameConfig::ENTITYSIZE;
		entityNodes[x][y].setType(EntityType::UNBREAKABLE_WALL);
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
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (entityNodes[i][j].getType() != EntityType::UNBREAKABLE_WALL)
				entityNodes[i][j].setType(EntityType::PATH);
		}
	}
	
	for (auto i : Entities::getInstance().getCharacters())
	{
		int x = i->getShape().getOrigin().x / GameConfig::ENTITYSIZE;
		int y = i->getShape().getOrigin().y / GameConfig::ENTITYSIZE;
		entityNodes[x][y].setType(EntityType::CHARACTER);
	}

	for (auto i : Entities::getInstance().getBreakableBlocks())
	{
		int x = i->getShape().getOrigin().x / GameConfig::ENTITYSIZE;
		int y = i->getShape().getOrigin().y / GameConfig::ENTITYSIZE;
		entityNodes[x][y].setType(EntityType::BREAKABLE_WALL);
	}
	
	setupRelationships();
}

void mapOfNodes::setupRelationships()
{
	EntityNode* child;
	int newI, newJ;
	
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			for (int k = -1; k < 2; k++)
			{
				newI = entityNodes[i][j].getY() / GameConfig::ENTITYSIZE + k;
				for (int l = -1; l < 2; l++)
				{
					newJ = entityNodes[i][j].getX() / GameConfig::ENTITYSIZE + l;
					if (newI >= 0 && newI < 21 && newJ >= 0 && newJ < 11)
					{
						child = &(entityNodes[newJ][newI]);
						if (child->getType() != EntityType::UNBREAKABLE_WALL && (newI!=i || newJ != j))
							entityNodes[i][j].addChild(child, 64);
					}
				}
			}
		}
	}
}

void mapOfNodes::setStart(int x, int y)
{
	pathGenerator.setStart(entityNodes[x][y]);
}

void mapOfNodes::setGoal()
{
	int iGoal, jGoal;
	float distance = 1000000;
	for(int i = 0; i < 11; i++)
		for (int j = 0; j < 21; j++)
		{
			if (entityNodes[i][j].getType() == EntityType::CHARACTER)
			{
				float newDistance = entityNodes[i][j].distanceTo(pathGenerator.getStart());
				if (newDistance < distance)
				{
					distance = newDistance;
					iGoal = i;
					jGoal = j;
				}
			}
		}
	pathGenerator.setGoal(entityNodes[iGoal][jGoal]);
}

int mapOfNodes::findPath()
{
	return pathGenerator.findPath<AStar>(path);
}

void mapOfNodes::setSecondaryGoal()
{
	int iGoal, jGoal;
	float distance = 1000000;
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 21; j++)
		{
			if (entityNodes[i][j].getType() == EntityType::BREAKABLE_WALL)
			{
				float newDistance = entityNodes[i][j].distanceTo(pathGenerator.getStart());
				if (newDistance < distance)
				{
					distance = newDistance;
					iGoal = i;
					jGoal = j;
				}
			}
		}
	pathGenerator.setGoal(entityNodes[iGoal][jGoal]);
}

void mapOfNodes::setPathToRunFromBomb()
{
	pathGenerator.setStart(*(pathGenerator.getGoal()));
	int iGoal, jGoal;
	float distance = 1000000;
	
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 21; j++)
		{
			if (entityNodes[i][j].getType() == EntityType::PATH)
			{
				distance = entityNodes[i][j].distanceTo(pathGenerator.getStart());
				if (distance > 128)
				{
					iGoal = i;
					jGoal = j;
					pathGenerator.setGoal(entityNodes[iGoal][jGoal]);
					if (pathGenerator.findPath<AStar>(path) == 1)
						return;					
				}
			}
		}
}