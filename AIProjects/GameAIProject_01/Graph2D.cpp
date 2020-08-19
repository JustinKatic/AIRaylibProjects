#include "Graph2D.h"
#include "Graph.h"
#include <iostream>
#include "Application.h"
#include "Player.h"


Graph2D::Graph2D()
{

}

Graph2D::~Graph2D()
{

}



void Graph2D::GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes)
{
	for (auto node : m_nodes)
	{
		float dist = Vector2Distance(position, node->data);
		if (dist < radius)
		{
			out_nodes.push_back(node);
		}
	}
}

bool Graph2D::FindPath(Node* startNode, std::function<bool(Node*)> isGoalNode, std::list<Node*>& out_path)
{
	std::list<PathFindNode*> stack;
	std::vector<PathFindNode*> alreadyProcessed;

	bool pathFound = false;

	//landa function to find is node already exists in either stack list or alreadyProcessed list
	auto GetNodeInLists = [&](Node* nodeToFind) -> PathFindNode*
	{
		for (auto& n : stack)
			if (n->graphNode == nodeToFind)
				return n;
		for (auto& n : alreadyProcessed)
			if (n->graphNode == nodeToFind)
				return n;
		return nullptr;
	};

	//create startNode values
	PathFindNode* pFNode = new PathFindNode();
	pFNode->gScore = 0.0f;
	pFNode->parent = nullptr;
	pFNode->graphNode = startNode;
	//landa function to find is node already exists in either stack list or alreadyProcessed list

	//push start node onto stack
	stack.push_back(pFNode);

	//while stack isnt empty
	while (!stack.empty())
	{
		//set current node to last node in stack list
		PathFindNode* currentNode = stack.back();
		//remove the last node from the stack list
		stack.pop_back();
		//put current node into alreadyProcessed list
		alreadyProcessed.push_back(currentNode);


		//if current node is the goal node store the path it used inside of out_path node
		if (isGoalNode(currentNode->graphNode))
		{
			PathFindNode* current = currentNode;
			while (current != nullptr)
			{
				out_path.push_front(current->graphNode);
				current = current->parent;
			}
			pathFound = true;
			break;
		}

		//for each edge in current nodes connections
		for (Edge& edge : currentNode->graphNode->connections)
		{

			float influenceCost = GetInfluenceValueAtPos(edge.to->data.x, edge.to->data.y) * 10;

			float gScore = currentNode->gScore + edge.data + influenceCost;

			//checks if current nodes connection is in stack list or stack list
			auto pFNodeChild = GetNodeInLists(edge.to);

			//if node wasnt in list 
			if (pFNodeChild == nullptr)
			{
				//create a new node
				PathFindNode* pFNodeChild = new PathFindNode();
				//add the currents node score to the PFNodeChild score
				pFNodeChild->gScore = gScore;
				//make PFNodeChilds parent = current node
				pFNodeChild->parent = currentNode;
				pFNodeChild->graphNode = edge.to;
				stack.push_back(pFNodeChild);
			}
			//node was found in stack list or visited 
			else
			{
				//update the nodes parent if its faster from this current node
				if (pFNodeChild->gScore > gScore)
				{
					pFNodeChild->parent = currentNode;
					pFNodeChild->gScore = gScore;
				}
			}
		}
		//sort stack so the lowest score node is at end of list
		stack.sort([&](PathFindNode* a, PathFindNode* b)
			{
				return a->gScore > b->gScore;
			});
	}

	for (auto pFNode : stack)
	{
		delete pFNode;
		pFNode = nullptr;
	}
	for (auto pFNode : alreadyProcessed)
	{
		delete pFNode;
		pFNode = nullptr;
	}

	return pathFound;
}

bool Graph2D::FindPath(Node* startNode, Node* goalNode, std::list<Node*>& out_path, bool useInfluence)
{
	std::list<PathFindNode*> stack;
	std::vector<PathFindNode*> alreadyProcessed;

	//landa function to find is node already exists in either stack list or alreadyProcessed list
	auto GetNodeInLists = [&](Node* nodeToFind) -> PathFindNode*
	{
		for (auto& n : stack)
			if (n->graphNode == nodeToFind)
				return n;
		for (auto& n : alreadyProcessed)
			if (n->graphNode == nodeToFind)
				return n;
		return nullptr;
	};

	//create startNode values
	PathFindNode* pFNode = new PathFindNode();
	pFNode->gScore = 0.0f;
	pFNode->hScore = 0.0f;
	pFNode->fScore = 0.0f;
	pFNode->parent = nullptr;
	pFNode->graphNode = startNode;

	//push start node onto stack
	stack.push_back(pFNode);

	//while stack isnt empty
	while (!stack.empty())
	{
		//set current node to last node in stack list
		PathFindNode* currentNode = stack.back();
		//remove the last node from the stack list
		stack.pop_back();
		//put current node into alreadyProcessed list
		alreadyProcessed.push_back(currentNode);


		//if current node is the goal node store the path it used inside of out_path node
		if (goalNode == currentNode->graphNode)
		{
			PathFindNode* current = currentNode;
			while (current != nullptr)
			{
				out_path.push_front(current->graphNode);
				current = current->parent;

			}
			return true;
		}

		//for each edge in current nodes connections
		for (Edge& edge : currentNode->graphNode->connections)
		{

			//checks if current nodes connection is in stack list or stack list
			float influenceMultiplier = useInfluence ? 1.0f : 0.0f;
			float influenceCost = influenceMultiplier * GetInfluenceValueAtPos(edge.to->data.x, edge.to->data.y) * 1000;

			auto pFNodeChild = GetNodeInLists(edge.to);


			float gScore = currentNode->gScore + edge.data + influenceCost;

			// TODO: optimise this. // Distance Squared from node to goalNode.
			float hScore = Vector2Distance(edge.to->data, goalNode->data); // *Vector2Distance(edge.to->data, goalNode->data);

			// Final Score.
			float fScore = gScore + hScore;

			//if node wasnt in list 
			if (pFNodeChild == nullptr)
			{
				//create a new node
				PathFindNode* pFNodeChild = new PathFindNode();
				//add the currents node score to the PFNodeChild score
				pFNodeChild->gScore = gScore;
				pFNodeChild->hScore = hScore;
				pFNodeChild->fScore = fScore;

				//make PFNodeChilds parent = current node
				pFNodeChild->parent = currentNode;
				pFNodeChild->graphNode = edge.to;
				stack.push_back(pFNodeChild);
			}
			//node was found in stack list or visited list
			else
			{
				if (pFNodeChild->gScore > gScore)
				{
					pFNodeChild->parent = currentNode;
					pFNodeChild->gScore = gScore;
					pFNodeChild->hScore = hScore;
					pFNodeChild->fScore = fScore;
				}
			}
		}
		//sort stack so the lowest score node is at end of list
		stack.sort([&](PathFindNode* a, PathFindNode* b)
			{
				return a->fScore > b->fScore;
			});
	}

	return false;
}



void Graph2D::SetInfluenceMap(std::vector<std::vector<float>>* influenceMap, int tileWidth, int tileHeight)
{
	m_influenceMap = influenceMap;
}

std::vector<std::vector<float>>& Graph2D::GetInfluenceMap()
{
	return m_influenceMap == nullptr ? emptyInfluenceMap : *m_influenceMap;
}

int Graph2D::GetInfluenceTileWidth()
{
	return m_tileWidth;
}
int Graph2D::GetInfluenceTileHeight()
{
	return m_tileHeight;
}

int Graph2D::GetInfluenceValue(int xId, int yId)
{
	auto& map = GetInfluenceMap();
	if (yId >= map.size())
		return 0;

	if (xId >= map[yId].size())
		return 0;

	return map[yId][xId];
}

int Graph2D::GetInfluenceValueAtPos(float xPos, float yPos)
{
	int toTileXId = xPos / GetInfluenceTileWidth();
	int toTileYId = yPos / GetInfluenceTileHeight();
	return GetInfluenceValue(toTileXId, toTileYId);
}