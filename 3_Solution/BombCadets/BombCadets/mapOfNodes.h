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

	void updateMapOfNodes();
	void setupRelationships();
	void setStart(int x, int y);
	void setGoal();
	int findPath();
	void setSecondaryGoal();
	void setPathToRunFromBomb();
	
public:
	static mapOfNodes& getInstance() {
		static mapOfNodes instance;
		return instance;
	}
};

