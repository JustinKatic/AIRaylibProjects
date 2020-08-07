#pragma once

#include "Graph.h"
#include "raymath.h"


class Graph2D : public Graph<Vector2, float>
{

protected:


	struct PathFindNode
	{
		Node* graphNode;
		PathFindNode* parent;
		float gScore;
		float hScore; // hiristic - manhatan distance (estimated cost to tavel to the goal node
		float fScore; // gScore + hScore
	};
	
public:


	Graph2D();
	virtual ~Graph2D();

	void GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes);

	// Dijkstras
	bool FindPath(Node* startNode, std::function<bool(Node*)>isGoalNode, std::list<Node*>& out_path);

	// AStar
	bool FindPath(Node* startNode, Node* goalNode, std::list<Node*>& out_path);



protected:

private:

};

