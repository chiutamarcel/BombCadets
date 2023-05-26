#include "MapOfNodes.h"
#include "Entities.h"
#include "GameConfig.h"

MapOfNodes::MapOfNodes()
{
	entityNodes = new EntityNode * [11];	
	for (int y = 0; y < 11; y++)
	{
		entityNodes[y] = new EntityNode [21];
		for (int x = 0; x < 21; x++)
		{
			entityNodes[y][x].setType(EntityType::PATH);
			int yy = (y + 2) * GameConfig::ENTITYSIZE;
			int xx = x * GameConfig::ENTITYSIZE ;
			entityNodes[y][x].setPosition(xx, yy);
		}
	}
	
	for (auto it : Entities::getInstance().getWalls())
	{
		int y = it->getShape().getPosition().y / 64 - 2;
		int x = it->getShape().getPosition().x / 64;
		entityNodes[y][x].setType(EntityType::UNBREAKABLE_WALL);
	}
}

MapOfNodes::~MapOfNodes()
{
	for (int y = 0; y < 11; y++)
	{
		delete[] entityNodes[y];
	}
	delete[] entityNodes;
}

MapOfNodes* MapOfNodes::getInstance()
{
	static MapOfNodes instance;
	return &instance;
}

void MapOfNodes::updateMapOfNodes()
{
	for (int y = 1; y < 10; y++)
	{
		for (int x = 1; x < 20; x++)
		{
			if (entityNodes[y][x].getType() != EntityType::UNBREAKABLE_WALL)
				entityNodes[y][x].setType(EntityType::PATH);
		}
	}
	
	for (auto it : Entities::getInstance().getBreakableBlocks())
	{
		int y = it->getShape().getPosition().y / 64 - 2;
		int x = it->getShape().getPosition().x / 64;
		entityNodes[y][x].setType(EntityType::BREAKABLE_WALL);
	}

	for (auto it : Entities::getInstance().getCharacters())
	{
		int y = it->getShape().getPosition().y / 64 - 2;
		int x = it->getShape().getPosition().x / 64;
		entityNodes[y][x].setType(EntityType::CHARACTER);
	}

	MapOfNodes::setRelationships();
}

void MapOfNodes::setRelationships()
{
	for (int y = 1; y < 10; y++)
	{
		for (int x = 1; x < 20; x++)
		{//entityNodes[y][x].getType() != EntityType::BREAKABLE_WALL &&
			if (this->option == 0) 
			{
				if (entityNodes[y][x].getType() != EntityType::UNBREAKABLE_WALL)
				{
					MapOfNodes::addChild(y, x, y - 1, x);

					MapOfNodes::addChild(y, x, y + 1, x);

					MapOfNodes::addChild(y, x, y, x - 1);

					MapOfNodes::addChild(y, x, y, x + 1);
				}
			}
			else
			{
				if (entityNodes[y][x].getType() != EntityType::BREAKABLE_WALL && entityNodes[y][x].getType() != EntityType::UNBREAKABLE_WALL)
				{
					MapOfNodes::addChild(y, x, y - 1, x);

					MapOfNodes::addChild(y, x, y + 1, x);

					MapOfNodes::addChild(y, x, y, x - 1);

					MapOfNodes::addChild(y, x, y, x + 1);
				}
			}
		}
	}
}

void MapOfNodes::addChild(int y, int x, int newY, int newX)
{
	EntityNode* child;
	if (this->option == 0)
	{
		if (entityNodes[newY][newX].getType() != EntityType::UNBREAKABLE_WALL)
		{
			child = &(entityNodes[newY][newX]);
			entityNodes[y][x].addChild(child, 54);
		}
	}
	else
	{
		if ((entityNodes[newY][newX].getType() != EntityType::UNBREAKABLE_WALL) && (entityNodes[newY][newX].getType() != EntityType::BREAKABLE_WALL))
		{
			child = &(entityNodes[newY][newX]);
			entityNodes[y][x].addChild(child, 54);
		}
	}
}

void MapOfNodes::setStart(int y, int x)
{
	pathGenerator.setStart(entityNodes[y][x]);
}

void MapOfNodes::setGoal()
{
	int yGoal = 15, xGoal = 15;
	float distance = 100000000;
	
	for (int y = 0; y < 11; y++)
		for (int x = 0; x < 21; x++)
		{
			if (entityNodes[y][x].getType() == EntityType::CHARACTER)
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
	//pathGenerator.setGoal(entityNodes[1][1]);
}

bool MapOfNodes::findPath()
{
	bool found = false;
	std::vector<EntityNode*> temp;
	MapOfNodes::getInstance()->getPath().clear();
	found = pathGenerator.findPath<AStar>(temp);
	
	path.swap(temp);
	
	return found;
}

void MapOfNodes::runFromBomb()
{
	int yGoal = 15, xGoal = 15;
	float distance = 100000000;
	
	for (int y = 1; y < 10; y++)
	{
		for (int x = 1; x < 20; x++)
		{
			if (entityNodes[y][x].getType() == EntityType::PATH)
			{
				float newDistance = entityNodes[y][x].distanceTo(pathGenerator.getStart());
				if (newDistance <= distance && newDistance > 192)
				{
					distance = newDistance;
					yGoal = y;
					xGoal = x;					
				}
			}
		}
	}

	pathGenerator.setGoal(entityNodes[yGoal][xGoal]);
	pathGenerator.findPath<AStar>(path);
		
}
