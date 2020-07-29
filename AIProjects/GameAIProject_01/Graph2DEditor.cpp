#include "Graph2DEditor.h"
#include "Graph2D.h"

Graph2DEditor::Graph2DEditor()
{

}

Graph2DEditor::~Graph2DEditor()
{

}

void Graph2DEditor::Update(float deltaTime)
{
	if (IsMouseButtonPressed(0))
	{
		auto mousePos = GetMousePosition();

		auto newNode = m_graph->AddNode(mousePos);

		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(mousePos, 60, nearbyNodes);

		for (auto nearbyNode : nearbyNodes)
		{
			float dist = Vector2Distance(newNode->data, nearbyNode->data);
			m_graph->AddEdge(newNode, nearbyNode, dist);
			m_graph->AddEdge(nearbyNode, newNode, dist);
		}
	}
}

void Graph2DEditor::Draw()
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
}

Graph2D* Graph2DEditor::GetGraph()
{
	return m_graph;
}

void Graph2DEditor::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}
