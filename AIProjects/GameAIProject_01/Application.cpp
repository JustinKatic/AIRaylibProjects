#include "Application.h"
#include "raylib.h"
#include "KeyBoardBehaviour.h"
#include "Behaviour.h"
#include "Player.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"


Application::Application()
{
	m_screenWidth = MAP_COLS * 30;
	m_screenHeight = MAP_ROWS * 30;
	m_tileWidth = m_screenWidth / MAP_COLS;
	m_tileHeight = m_screenHeight / MAP_ROWS;

}
Application::~Application()
{

}


//Game loop
void Application::Run()
{
	InitWindow(m_screenWidth, m_screenHeight, "AIE AI manager");

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


	//int numRows = 19;
	//int numCols = 27;
	//float xOffset = 50;
	//float yOffset = 50;
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
	//	m_graph->GetNearbyNodes(node->data, 80, nearbyNodes);

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



	m_graph = new Graph2D();
	m_graphEditor = new Graph2DEditor();
	m_graphEditor->SetGraph(m_graph);


	auto player = new Player();
	player->SetFriction(1.0f);
	//player->SetPosition({ m_screenWidth * 0.25f, m_windowHeight * 0.5f });
	player->SetEditor(m_graphEditor);
	m_player1 = player;


	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (int x = 0; x < MAP_COLS; x++)
		{
			int xPos = x * m_tileWidth;
			int yPos = y * m_tileHeight;
			int tileID = m_map[y][x];

			if (tileID == START)
			{
				player->SetPosition({(float)xPos + m_tileWidth /2,(float)yPos + m_tileHeight /2});
			}
		}
	}

}
void Application::Unload()
{
	delete m_player1;
	m_player1 = nullptr;

	//===============================================================================================================
	delete m_graphEditor;
	m_graphEditor = nullptr;
	delete m_graph;
	m_graph = nullptr;
	//===============================================================================================================
}
void Application::Update(float dt)
{
	m_player1->Update(dt);
	//===============================================================================================================
	m_graphEditor->Update(dt);
	//===============================================================================================================
}
void Application::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);


	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (size_t x = 0; x < MAP_COLS; x++)
		{
			int xPos = x * m_tileWidth;
			int yPos = y * m_tileHeight;
			int tileID = m_map[y][x];

			if (tileID == WALL)
			{
				DrawRectangle(xPos, yPos, m_tileWidth, m_tileHeight, GREEN);
			}
			if (tileID == FOOD)
			{
				DrawCircle(xPos + m_tileWidth/2, yPos + m_tileHeight /2, 5, YELLOW);
			}
			if (tileID == POWERUP)
			{
				DrawCircle(xPos + m_tileWidth / 2, yPos + m_tileHeight / 2, 8, ORANGE);
			}

		}
	}
	//===============================================================================================================
	m_graphEditor->Draw();
	//===============================================================================================================
	m_player1->Draw();
	//===============================================================================================================
	EndDrawing();
}


