#include "Application.h"
#include "raylib.h"
#include "KeyBoardBehaviour.h"
#include "Behaviour.h"
#include "Player.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include <iostream>


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
		UpdateInfluence(dt);
		Draw();
	}
	Unload();

	CloseWindow();
}

void Application::Load()
{
	//===============================================================================================================
	//LOADING TEXTURES
	//===============================================================================================================
	backGroundImg = LoadImage("../pacManSprites/space.png");
	backGroundTex = LoadTextureFromImage(backGroundImg);

	wallImg = LoadImage("../pacManSprites/neonSquare.png");
	wallTex = LoadTextureFromImage(wallImg);

	sideWallImg = LoadImage("../pacManSprites/neonSquareSide.png");
	sideWallTex = LoadTextureFromImage(sideWallImg);

	topBottomWallImg = LoadImage("../pacManSprites/neonSquareTopBottom.png");
	topBottomWallTex = LoadTextureFromImage(topBottomWallImg);

	topBottomWallImg = LoadImage("../pacManSprites/neonSquareTopBottom.png");
	topBottomWallTex = LoadTextureFromImage(topBottomWallImg);

	safeBoxImg = LoadImage("../pacManSprites/neonSquareSafeBox.png");
	safeBoxTex = LoadTextureFromImage(safeBoxImg);

	VImg = LoadImage("../pacManSprites/V.png");
	VTex = LoadTextureFromImage(VImg);

	//===============================================================================================================
	//SETTING COLLISION BOXES
	//===============================================================================================================
	noGo = std::vector<Rect>({

		//safeZoneBox
		{ {5.0f * m_tileWidth, 5.0f * m_tileHeight}, { 6.0f * m_tileWidth, 3.0f * m_tileHeight }},
		{ {5.0f * m_tileWidth, 8.0f * m_tileHeight}, { 2.0f * m_tileWidth, 2.0f * m_tileHeight }},
		{ {5.0f * m_tileWidth, 10.0f * m_tileHeight}, { 6.0f * m_tileWidth, 3.0f * m_tileHeight }},

		//top row recs
		{ {15.0f * m_tileWidth, 5.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },
		{ {25.0f * m_tileWidth, 5.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },
		{ {35.0f * m_tileWidth, 5.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },
		{ {45.0f * m_tileWidth, 5.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },

		//bottom row recs
		{ {5.0f * m_tileWidth, 17.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },
		{ {15.0f * m_tileWidth, 17.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },
		{ {25.0f * m_tileWidth, 17.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },
		{ {35.0f * m_tileWidth, 17.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },
		{ {45.0f * m_tileWidth, 17.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight} },

		//top wall
		{ {0.0f * m_tileWidth, 0.0f * m_tileHeight}, { 56.0f * m_tileWidth, 1.0f * m_tileHeight} },
		//bottom wall
		{ {0.0f * m_tileWidth, 29.0f * m_tileHeight}, {56.0f * m_tileWidth, 1.0f * m_tileHeight} },
		//left wall
		{ {0.0f * m_tileWidth, 0.0f * m_tileHeight}, { 1.0f * m_tileWidth, 30.0f * m_tileHeight} },
		//right wall
		{ {55.0f * m_tileWidth, 0.0f * m_tileHeight}, { 1.0f * m_tileWidth, 30.0f * m_tileHeight} },

		//topleft box for player
		{ {5.0f * m_tileWidth, 5.0f * m_tileHeight}, { 6.0f * m_tileWidth, 8.0f * m_tileHeight }},

		});

	//===============================================================================================================
	//creating influence map and populating each element with 0
	//===============================================================================================================
	for (int y = 0; y < MAP_ROWS; y++)
	{
		m_influence.push_back(std::vector<float>()); // add a row
		for (int x = 0; x < MAP_COLS; x++)
		{
			m_influence[y].push_back(0); // add value to row
		}
	}
	//===============================================================================================================
	//creating instance of graph
	//===============================================================================================================
	m_graph = new Graph2D();
	m_graph->SetInfluenceMap(&m_influence, m_tileWidth, m_tileHeight);
	m_graphEditor = new Graph2DEditor();
	m_graphEditor->SetGraph(m_graph);

	//===============================================================================================================
	//creating instance of game objects
	//===============================================================================================================
	auto player = new Player(this);
	player->SetFriction(1.0f);
	m_player = player;

	auto redGhost = new RedGhost(this);
	redGhost->SetFriction(1.0f);
	redGhost->SetEditor(m_graphEditor);
	redGhost->SetPlayer(player);
	m_redGhost = redGhost;

	auto blueGhost = new BlueGhost(this);
	blueGhost->SetFriction(1.0f);
	blueGhost->SetPlayer(player);
	m_blueGhost = blueGhost;

	//===============================================================================================================
	//setting postions for gameObjects and nodes inside of tile map
	//===============================================================================================================

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
			if (tileID == FOOD || tileID == START || tileID == POWERUP || tileID == REDGHOST || tileID == BLUEGHOST || tileID == SAFEPATH || tileID == SAFEENTRY || tileID == SAFEENTRYDOOR)
			{
				m_graph->AddNode({ (float)xPos + m_tileWidth / 2,(float)yPos + m_tileHeight / 2 });
			}
			if (tileID == REDGHOST)
			{
				redGhost->SetPosition({ (float)xPos + m_tileWidth / 2,(float)yPos + m_tileHeight / 2 });
			}
			if (tileID == BLUEGHOST)
			{
				blueGhost->SetPosition({ (float)xPos + m_tileWidth / 2,(float)yPos + m_tileHeight / 2 });
			}
		}
	}

	//===============================================================================================================
	//setting connections between nodes and adding there data
	//===============================================================================================================
	for (auto node : m_graph->GetNodes())
	{
		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(node->data, 40, nearbyNodes);

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

//===============================================================================================================
//UNLOADING NEW CREATED INSTANCES
//===============================================================================================================
void Application::Unload()
{
	delete m_player;
	m_player = nullptr;

	delete m_redGhost;
	m_redGhost = nullptr;

	//===============================================================================================================
	delete m_graphEditor;
	m_graphEditor = nullptr;
	delete m_graph;
	m_graph = nullptr;
	//===============================================================================================================
}
Player* Application::GetPlayer()
{
	return (Player*)m_player;
}
Graph2D* Application::GetGraph()
{
	return m_graph;
}
void Application::Update(float dt)
{
	m_player->Update(dt);
	//===============================================================================================================
	m_redGhost->Update(dt);
	//===============================================================================================================
	m_blueGhost->Update(dt);
	//===============================================================================================================
	m_graphEditor->Update(dt);
	//===============================================================================================================

	 // what tile index is pacman on?
	int currentIndexX = (m_player->GetPosition().x) / m_tileWidth;
	int currentIndexY = (m_player->GetPosition().y) / m_tileHeight;
	
	//if pacman is on specified index do following
	if (m_map[currentIndexY][currentIndexX] == FOOD)
	{
		m_score += 1;
		m_map[currentIndexY][currentIndexX] = EMPTY;
	}
	if (m_map[currentIndexY][currentIndexX] == POWERUP)
	{
		m_player->SetPowerUpBool(true);
		m_map[currentIndexY][currentIndexX] = EMPTY;
	}
}

//===============================================================================================================
//updating influence map
//===============================================================================================================
void Application::UpdateInfluence(float deltaTime)
{
	// what tile index is pacman on?
	int currentIndexX = (m_player->GetPosition().x) / m_tileWidth;
	int currentIndexY = (m_player->GetPosition().y) / m_tileHeight;

	int T = currentIndexY - 2;
	int B = currentIndexY + 2;
	int L = currentIndexX - 2;
	int R = currentIndexX + 2;

	T = (T < 0) ? 0 : T;
	B = (B > MAP_ROWS - 1) ? MAP_ROWS - 1 : B;
	L = (L < 0) ? 0 : L;
	R = (R > MAP_COLS - 1) ? MAP_COLS - 1 : R;

	for (int y = T; y <= B; y++)
	{
		for (int x = L; x <= R; x++)
		{
			m_influence[y][x] += 0.02;
		}
	}

	for (int y = 0; y < m_influence.size(); y++)
	{
		for (int x = 0; x < m_influence[y].size(); x++)
		{
			m_influence[y][x] -= 0.01;
			if (m_influence[y][x] < 0)
			{
				m_influence[y][x] = 0;
			}
			if (m_influence[y][x] > 1)
			{
				m_influence[y][x] = 1;
			}
		}
	}
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawTexture(backGroundTex, 0, 0, WHITE);

	char score[20];
	sprintf_s(score, "%d", m_score);

	DrawText(score, 50, 50, 50, GREEN);

	//===============================================================================================================
	// drawing sprites textures
	//===============================================================================================================
	DrawTexture(safeBoxTex, 5.0f * m_tileWidth, 5.0f * m_tileHeight, WHITE);

	DrawTexture(topBottomWallTex, 0.0f * m_tileWidth, 0.0f * m_tileHeight, WHITE);
	DrawTexture(topBottomWallTex, 0.0f * m_tileWidth, 29.0f * m_tileHeight, WHITE);
	DrawTexture(sideWallTex, 0.0f * m_tileWidth, 0.0f * m_tileHeight, WHITE);
	DrawTexture(sideWallTex, 55.0f * m_tileWidth, 0.0f * m_tileHeight, WHITE);

	DrawTexture(wallTex, 15.0f * m_tileWidth, 5.0f * m_tileHeight, WHITE);
	DrawTexture(wallTex, 25.0f * m_tileWidth, 5.0f * m_tileHeight, WHITE);
	DrawTexture(wallTex, 35.0f * m_tileWidth, 5.0f * m_tileHeight, WHITE);
	DrawTexture(wallTex, 45.0f * m_tileWidth, 5.0f * m_tileHeight, WHITE);

	DrawTexture(wallTex, 5.0f * m_tileWidth, 17.0f * m_tileHeight, WHITE);
	DrawTexture(wallTex, 15.0f * m_tileWidth, 17.0f * m_tileHeight, WHITE);
	DrawTexture(wallTex, 25.0f * m_tileWidth, 17.0f * m_tileHeight, WHITE);
	DrawTexture(wallTex, 35.0f * m_tileWidth, 17.0f * m_tileHeight, WHITE);
	DrawTexture(wallTex, 45.0f * m_tileWidth, 17.0f * m_tileHeight, WHITE);

	//===============================================================================================================
	//Drawing sprites at specfied position in tile map
	//===============================================================================================================
	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (size_t x = 0; x < MAP_COLS; x++)
		{
			int xPos = x * m_tileWidth;
			int yPos = y * m_tileHeight;
			int tileID = m_map[y][x];

			if (tileID == FOOD)
			{
				DrawCircle(xPos + m_tileWidth / 2, yPos + m_tileHeight / 2, 6, YELLOW);
			}
			if (tileID == POWERUP)
			{
				DrawTexture(VTex, xPos + m_tileWidth / 2 - VTex.width / 2, yPos + m_tileHeight / 2 - VTex.height / 2, WHITE);
			}
		}
	}
	//===============================================================================================================
	m_graphEditor->Draw();
	//===============================================================================================================
	m_redGhost->Draw();
	//===============================================================================================================
	m_blueGhost->Draw();
	//===============================================================================================================
	m_player->Draw();
	//===============================================================================================================

	//debug drawing of infuence map
	if (IsKeyDown(KEY_FIVE))
	{
		DrawInfluenceMap();
	}

	//gameover screen
	if (gameOver == true)
	{
		DrawTexture(backGroundTex, 0, 0, WHITE);
		DrawText("LOSER!!!", 300, 300, 350, GREEN);
	}
	EndDrawing();
}

//===============================================================================================================
//drawing heatmap
//===============================================================================================================
void Application::DrawInfluenceMap()
{
	for (int y = 0; y < m_influence.size(); y++)
	{
		for (int x = 0; x < m_influence[y].size(); x++)
		{
			float xPos = x * m_tileWidth;
			float yPos = y * m_tileHeight;

			auto color = YELLOW;
			color.a = 255 * ((m_influence[y][x] * 0.5f) + 0.1f);
			DrawRectangle(xPos, yPos, m_tileWidth, m_tileHeight, color);
		}
	}
}