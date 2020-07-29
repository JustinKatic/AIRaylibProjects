#include "Application.h"
#include "raylib.h"
#include "KeyBoardBehaviour.h"
#include "Behaviour.h"
#include "Player.h"

#include "Graph2D.h"
#include "Graph2DEditor.h"


Application::Application(int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{

}
Application::~Application()
{

}


//Game loop
void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "AIE AI manager");

	Load();

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		Update(dt);
		Draw();
	}
	Unload();

	CloseWindow();
}

void Application::Load()
{
	//===============================================================================================================
	//m_graph = new Graph2D();

	//int numRows = 4;
	//int numCols = 6;
	//float xOffset = 100;
	//float yOffset = 100;
	//float spacing = 50;
	//
	//for (int y = 0; y < numRows; y++)
	//{
	//	for (int x = 0; x < numCols; x++)
	//	{
	//		m_graph->AddNode({
	//			x * spacing + xOffset,
	//			y * spacing + yOffset
	//			});
	//	}
	//}

	//for (auto node : m_graph->GetNodes())
	//{
	//	std::vector<Graph2D::Node*> nearbyNodes;
	//	m_graph->GetNearbyNodes(node->data, 60, nearbyNodes);

	//	for (auto connectedNode : nearbyNodes)
	//	{
	//		if (connectedNode == node)
	//		{
	//			continue;
	//		}
	//			float dist = Vector2Distance(node->data, connectedNode->data);
	//			m_graph->AddEdge(node, connectedNode, dist);
	//			m_graph->AddEdge(connectedNode, node, dist);	
	//	}
	//}

	//===============================================================================================================

	//m_graphEditor = new Graph2DEditor();
	//m_graphEditor->SetGraph(m_graph);


	m_player1 = new Player();
	m_player1->SetFriction(1.0f);
	m_player1->SetPosition({ m_windowWidth * 0.25f, m_windowHeight * 0.5f });

}
void Application::Unload()
{
	delete m_player1; m_player1 = nullptr;

	//===============================================================================================================
	//delete m_graphEditor;
	//m_graphEditor = nullptr;
	//delete m_graph;
	//m_graph = nullptr;
	//===============================================================================================================
}
void Application::Update(float dt)
{
	m_player1->Update(dt);
	//===============================================================================================================
	//m_graphEditor->Update(dt);
	//===============================================================================================================
}
void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	//===============================================================================================================
	//m_graphEditor->Draw();
	//===============================================================================================================
	m_player1->Draw();
	EndDrawing();
}


//TODO: 
// fix hard coded 60 value representing radius of nearby nodes to connect
// add variables to customise the graphs2dEditors
//- node colour
//- line colour
//-node radius
//-node outline

//-prevent nodes from being placed ontop of other nodes

//challange
//can you save and load graph to file
//xml json custom binary format
//tinyXML
