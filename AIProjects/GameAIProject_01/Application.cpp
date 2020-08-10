#include "Application.h"
#include "raylib.h"
#include "KeyBoardBehaviour.h"
#include "Behaviour.h"
#include "Player.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"
#include "RedGhost.h"


Application::Application()
{
	m_screenWidth = MAP_COLS * 33;
	m_screenHeight = MAP_ROWS * 33;
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

	m_graph = new Graph2D();
	m_graphEditor = new Graph2DEditor();
	m_graphEditor->SetGraph(m_graph);


	auto player = new Player();
	player->SetFriction(1.0f);
	m_player1 = player;

	auto redGhost = new RedGhost();
	redGhost->SetFriction(1.0f);
	redGhost->SetEditor(m_graphEditor);
	m_redGhost = redGhost;



	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (int x = 0; x < MAP_COLS; x++)
		{
			int xPos = x * m_tileWidth;
			int yPos = y * m_tileHeight;
			int tileID = m_map[y][x];

			if (tileID == START)
			{
				player->SetPosition({ (float)xPos + m_tileWidth / 2,(float)yPos + m_tileHeight / 2 });
			}
			if (tileID == FOOD || tileID == START || tileID == POWERUP || tileID == REDGHOST || tileID == BLUEGHOST)
			{
				m_graph->AddNode({ (float)xPos + m_tileWidth / 2,(float)yPos + m_tileHeight / 2 });
			}
			if (tileID == REDGHOST)
			{
				redGhost->SetPosition({ (float)xPos + m_tileWidth / 2,(float)yPos + m_tileHeight / 2 });
			}
		}

		for (auto node : m_graph->GetNodes())
		{
			std::vector<Graph2D::Node*> nearbyNodes;
			m_graph->GetNearbyNodes(node->data, 50, nearbyNodes);

			for (auto connectedNode : nearbyNodes)
			{
				if (connectedNode == node)
				{
					continue;
				}
				float dist = Vector2Distance(node->data, connectedNode->data);
				m_graph->AddEdge(node, connectedNode, dist);
				m_graph->AddEdge(connectedNode, node, dist);
			}
		}
	}
}
	


void Application::Unload()
{
	delete m_player1;
	m_player1 = nullptr;

	delete m_redGhost;
	m_redGhost = nullptr;

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
	m_redGhost->Update(dt);
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
				DrawCircle(xPos + m_tileWidth / 2, yPos + m_tileHeight / 2, 5, YELLOW);
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
	m_redGhost->Draw();
	//===============================================================================================================
	m_player1->Draw();
	//===============================================================================================================
	EndDrawing();
}


