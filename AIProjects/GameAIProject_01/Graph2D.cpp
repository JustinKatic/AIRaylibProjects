#include "Graph2D.h"
#include "Graph.h"


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
				
				//TODO: need to set current node to currents parent
			}
			return true;
		}

		//for each edge in current nodes connections
		for (Edge& edge : currentNode->graphNode->connections)
		{
			//checks if current nodes connection is in stack list or stack list
			auto pFNodeChild = GetNodeInLists(edge.to);

			//if node wasnt in list 
			if (pFNodeChild == nullptr)
			{
				//create a new node
				PathFindNode* pFNodeChild = new PathFindNode();
				//add the currents node score to the PFNodeChild score
				pFNodeChild->gScore = currentNode->gScore + edge.data;
				//make PFNodeChilds parent = current node
				pFNodeChild->parent = currentNode;
				pFNodeChild->graphNode = edge.to;
				stack.push_back(pFNodeChild);
			}
			//node was found in stack list or visited list
			else
			{
				if (pFNodeChild->gScore > currentNode->gScore + edge.data)
				{
					pFNodeChild->parent = currentNode;
					pFNodeChild->gScore = currentNode->gScore + edge.data;
				}
			}
		}
		//sort stack so the lowest score node is at end of list
		stack.sort([&](PathFindNode* a, PathFindNode* b)
			{
				return a->gScore > b->gScore;
			});
	}

	return false;
}

bool Graph2D::FindPath(Node* startNode, Node* goalNode, std::list<Node*>& out_path)
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
		//TODO: not entering loop
		if (goalNode == currentNode->graphNode)
		{
			PathFindNode* current = currentNode;
			while (current != nullptr)
			{
				out_path.push_front(current->graphNode);
				current = current->parent;

				//TODO: need to set current node to currents parent
			}
			return true;
		}

		//for each edge in current nodes connections
		for (Edge& edge : currentNode->graphNode->connections)
		{
			//checks if current nodes connection is in stack list or stack list
			auto pFNodeChild = GetNodeInLists(edge.to);

			float gScore = currentNode->gScore + edge.data;

			// TODO: optimise this. // Distance Squared from node to goalNode.
			float hScore = Vector2Distance(edge.to->data, goalNode->data) * Vector2Distance(edge.to->data, goalNode->data);

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
				if (pFNodeChild->fScore > fScore)
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

// PATHMODE:ASTAR, PATHMODE::DIJKSTRAS, PATHMODE::BFS, PATHMODE::DFS
