#pragma once
#include "EntityNode.h"
#include "src/AStar.h"
#include "src/PathFinder.h"

#include <vector>

class mapOfNodes
{
private:
	EntityNode** entityNodes;
	std::vector<EntityNode*> path;
	PathFinder<EntityNode> pathGenerator;
	
	mapOfNodes();
	~mapOfNodes();

	
public:
	void updateMapOfNodes();
	void setupRelationships();
	void setStart(int x, int y);
	void setGoal();
	int findPath();
	void setSecondaryGoal();
	void setPathToRunFromBomb();
	float distanceToGoal();
	EntityNode *getGoal();
	std::vector<EntityNode*> getPath();
	void addChild(int y, int x, int newY, int newX);
	static mapOfNodes& getInstance() {
		static mapOfNodes instance;
		return instance;
	}
	EntityNode** getEntityNodes() {
		return entityNodes;
	}
};

