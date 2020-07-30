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
		Edge e = { nodeB,data };
		nodeA->connections.push_back({ nodeB,data });
	}
	//========================================================================================
	//Get Nodes
	//========================================================================================
	const std::vector<Node*>& GetNodes()
	{
		return m_nodes;
	}

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
				stack.push_back(edge.to);
			}
		}
		return nullptr;
	}

protected:

	std::vector<Node*> m_nodes;

private:
};

