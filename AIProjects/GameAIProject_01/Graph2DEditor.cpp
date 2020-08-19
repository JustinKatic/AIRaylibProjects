#include "Graph2DEditor.h"
#include "Graph2D.h"
#include "raylib.h"

Graph2DEditor::Graph2DEditor()
{

}

Graph2DEditor::~Graph2DEditor()
{

}

void Graph2DEditor::Update(float deltaTime)
{
	//create path node
	if (IsKeyDown(KEY_N))
	{
		auto mousePos = GetMousePosition();
		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(mousePos, GetConnectionRadius(), nearbyNodes);
		for (int i = 0; i < nearbyNodes.size(); i++) {
			float dist = Vector2Distance(mousePos, nearbyNodes[i]->data);
			if (dist < 30)
			{
				return;
			}
		}
		auto newNode = m_graph->AddNode(mousePos);
		for (auto nearbyNode : nearbyNodes)
		{
			float dist = Vector2Distance(newNode->data, nearbyNode->data);
			m_graph->AddEdge(newNode, nearbyNode, dist);
			m_graph->AddEdge(nearbyNode, newNode, dist);
		}
	}

	//create wall node
	if (IsKeyDown(KEY_ZERO))
	{
		auto mousePos = GetMousePosition();
		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(mousePos, GetConnectionRadius(), nearbyNodes);
		for (int i = 0; i < nearbyNodes.size(); i++) {
			float dist = Vector2Distance(mousePos, nearbyNodes[i]->data);
			if (dist < 30)
			{
				return;
			}
		}
		auto newNode = m_graph->AddNode(mousePos);
		for (auto nearbyNode : nearbyNodes)
		{
			float dist = Vector2Distance(newNode->data, nearbyNode->data);
			m_graph->AddEdge(newNode, nearbyNode, 1000);
			m_graph->AddEdge(nearbyNode, newNode, 1000);
		}
	}

	if (IsMouseButtonPressed(1))
	{
		m_endNodeFound = false;
		// get the first node that we click on.
		std::vector<Graph2D::Node*> neighbouringNodes;
		m_graph->GetNearbyNodes(GetMousePosition(), 8, neighbouringNodes);
		if (neighbouringNodes.empty() == false)
		{
			if (m_startNode == nullptr)
			{
				m_startNode = neighbouringNodes[0];
			}

			else if (m_endNode == nullptr)
			{
				m_endNode = neighbouringNodes[0];
			}

			else 
			{ 
				m_startNode = neighbouringNodes[0]; m_endNode = nullptr;
			}

			// Begin Search
			// call the FindPath method
			if (m_endNode != nullptr)
			{
				
				std::list<Graph2D::Node*> path; // stores the path

				if (m_graph->FindPath(m_startNode, m_endNode, path, false) == true)
				{
					//populate the std::vector<Vetor2> path with our path data.
					m_path.clear();
					for (auto pathnode : path)
					{
						m_path.push_back(pathnode->data);
					}
					m_endNodeFound = true;
				}
			}
		}
	}
}

void Graph2DEditor::Draw()
{
	if (IsKeyDown(KEY_FIVE))
	{
		//draw all connections
		for (auto node : m_graph->GetNodes())
		{
			for (auto connections : node->connections)
			{
				DrawLine(node->data.x, node->data.y, connections.to->data.x, connections.to->data.y, GRAY);
			}
		}

		//draw all nodes
		for (auto node : m_graph->GetNodes())
		{
			DrawCircle(node->data.x, node->data.y, 8, LIGHTGRAY);
			DrawCircleLines(node->data.x, node->data.y, 8, GRAY);
		}


		//draw a preview node where the mouse is
		auto mousePos = GetMousePosition();
		DrawCircle(mousePos.x, mousePos.y, 6, LIGHTGRAY);

		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(mousePos, 60, nearbyNodes);

		for (auto nearbyNode : nearbyNodes)
		{
			DrawLine(mousePos.x, mousePos.y, nearbyNode->data.x, nearbyNode->data.y, LIGHTGRAY);
		}

		if (m_startNode != nullptr)
		{
			DrawCircle(m_startNode->data.x, m_startNode->data.y, 6, GREEN);
		}
		if (m_endNode != nullptr)
		{
			DrawCircle(m_endNode->data.x, m_endNode->data.y, 4, RED);
		}
		if (m_endNodeFound == true && m_endNode != nullptr)
		{
			DrawCircle(m_endNode->data.x, m_endNode->data.y, 2, YELLOW);
		}


		if (!m_path.empty())
		{
			for (int i = 0; i < m_path.size() - 1; i++)
			{
				DrawLineEx(m_path[i], m_path[i + 1], 5, GREEN);
			}
		}
	}
}

Graph2D* Graph2DEditor::GetGraph()
{
	return m_graph;
}

void Graph2DEditor::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}

const float Graph2DEditor::GetConnectionRadius() const
{
	return m_connectionRadius;
}

void Graph2DEditor::SetConnectionRadius(float radius)
{
	m_connectionRadius = radius;
}

