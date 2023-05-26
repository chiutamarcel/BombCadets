#pragma once
#include "EntityNode.h"
#include "src/AStar.h"
#include "src/PathFinder.h"

class MapOfNodes
{
private:
	EntityNode** entityNodes;
	std::vector<EntityNode*> path;
	PathFinder<EntityNode> pathGenerator;
	int option = 0;
	
	MapOfNodes();
	~MapOfNodes();
	
public:
	static MapOfNodes* getInstance();
	
	void updateMapOfNodes();
	void setRelationships();
	void addChild(int y, int x, int newY, int newX);
	void setStart(int y, int x);
	void setGoal();
	bool findPath();
	void runFromBomb();
	void setOption(int value) { option = value; }
	int getOption() { return option; }
	
	std::vector<EntityNode*> &getPath() { return path; }
	EntityNode** getEntityNodes() { return entityNodes; }
	EntityNode* getGoal() { return pathGenerator.getGoal(); }
	EntityNode* getStart() { return pathGenerator.getStart(); }
};

