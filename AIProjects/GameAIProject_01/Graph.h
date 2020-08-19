#pragma once
#include <vector>
#include <functional>
#include<list>

template<class TNodeData, class TEdgeData>
class Graph
{
public:
	struct Node;
	struct Edge;


	struct Node
	{
		TNodeData data;
		std::vector<Edge> connections;
	};

	struct Edge
	{
		Node* to;
		TEdgeData data;
	};


public:
	//========================================================================================
	//Constructor
	//========================================================================================
	Graph()
	{

	}
	//========================================================================================
	//Destructor
	//========================================================================================
	virtual ~Graph()
	{
		for (auto node : m_nodes)
		{
			delete node;
		}
		m_nodes.clear();
	}
	//========================================================================================
	//Add Node
	//========================================================================================
	Node* AddNode(const TNodeData& data)
	{
		Node* node = new Node();
		node->data = data;

		m_nodes.push_back(node);
		return node;
	}
	//========================================================================================
	//Add Edge
	//========================================================================================
	void AddEdge(Node* nodeA, Node* nodeB, const TEdgeData& data)
	{
		nodeA->connections.push_back({ nodeB,data });
	}
	//========================================================================================
	//Get Nodes
	//========================================================================================
	const std::vector<Node*>& GetNodes()
	{
		return m_nodes;
	}


	//========================================================================================
	//BFS
	//========================================================================================
	/*
	1.push start nide on stack
	2.while stack !empty
		-current node = stack node
		-stack.pop.front()
		-visted.push(currentnode)
		-process current node

	3.foreach connection
		-if (connection.to not in stack or visited list
		{
			stack.push (connection.to)
		}
	*/
	Node* ForEachBFS(Node* startNode, std::function<bool(Node* n)> process)
	{
		std::vector<Node*> stack;
		std::vector<Node*> visited;

		if (startNode == nullptr)
		{
			startNode = m_nodes[0];
		}
		stack.push_back(startNode);

		while (stack.empty() == false)
		{
			//get node at front of stack and then remove the node from the stack
			Node* n = stack.back();
			stack.pop_back();
			//add the node to the visited list
			visited.push_back(n);
			process(n);

			//add children in the stack if they have not been visted
			for (Edge& edge : n->connections)
			{
				//does the node exist in the visited list or stack list?
				bool inStack = std::find(stack.begin(), stack.end(), edge.to) != stack.end();
				bool inVisited = std::find(visited.begin(), visited.end(), edge.to) != visited.end();

				//if true go back to top of while loop
				if (inStack == true || inVisited == true)
				{
					continue;
				}
				//if was not in list push back edge.to into stack list
				stack.push_back(edge.to);

			}
		}
		return nullptr;
	}

	//========================================================================================
	//DFS
	//========================================================================================
	Node* ForEachDFS(Node* startNode, std::function<bool(Node* n)> process)
	{
		std::vector<Node*> stack;
		std::vector<Node*> visited;

		if (startNode == nullptr)
		{
			startNode = m_nodes[0];
		}
		stack.push_back(startNode);

		while (stack.empty() == false)
		{
			Node* n = stack.back();
			stack.pop_back();
			visited.push_back(n);
			process(n);

			for (Edge& edge : n->connections)
			{
				bool inStack = std::find(stack.begin(), stack.end(), edge.to) != stack.end();
				bool inVisited = std::find(visited.begin(), visited.end(), edge.to) != visited.end();

				if (inStack == true || inVisited == true)
				{
					continue;
				}
				stack.insert(stack.begin(), edge.to);
			}
		}
		return nullptr;
	}

protected:

	std::vector<Node*> m_nodes;

private:
};

