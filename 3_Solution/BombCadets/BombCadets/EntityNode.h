#pragma once
#include "src/AStar.h"

enum class EntityType {
	PATH,
	BREAKABLE_WALL,
	UNBREAKABLE_WALL,
	CHARACTER
};

class EntityNode :
    public AStarNode
{
private:
	EntityType type;
public:
	EntityNode(){}
	
	~EntityNode() {}

	void setType(EntityType type) { this->type = type; }
	EntityType getType() { return type; }
	
	float distanceTo(AStarNode* node) const
	{
		int newX = m_x - node->getX(), newY = m_y - node->getY();
		return sqrtf(static_cast<float>(newX * newX + newY * newY));
	}
};
