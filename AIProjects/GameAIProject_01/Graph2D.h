#pragma once

#include "Graph.h"
#include "raymath.h"

class Application;

class Graph2D : public Graph<Vector2, float>
{

protected:

	Application* m_app;


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
	bool FindPath(Node* startNode, Node* goalNode, std::list<Node*>& out_path, bool useInfluence);

	void SetInfluenceMap(std::vector<std::vector<float>>* influenceMap, int tileWidth, int tileHeight);
	std::vector<std::vector<float>>& GetInfluenceMap();
	int GetInfluenceValue(int xId, int yId);
	int GetInfluenceValueAtPos(float xPos, float yPos);
	int GetInfluenceTileWidth();
	int GetInfluenceTileHeight();




protected:

	std::vector<std::vector<float>> emptyInfluenceMap;
	std::vector<std::vector<float>>* m_influenceMap;
	int m_tileWidth = 33;
	int m_tileHeight = 33;

private:

};

