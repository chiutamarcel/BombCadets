#pragma once
#include "src/AStar.h"

enum class EntityType {
	CHARACTER,
	PATH,
	BREAKABLE_WALL,
	UNBREAKABLE_WALL
};

class EntityNode:
	public AStarNode
{
private:
	EntityType type;
public:
	EntityNode(){}
	~EntityNode(){}
	
	void setType(EntityType type)
	{
		this->type = type;
	}
	
	EntityType getType() { return type; }

	float distanceTo(AStarNode* node) const
	{
		int x = this->getX() - node->getX();
		int y = this->getY() - node->getY();
		return sqrt(x * x + y * y);
	}
};

