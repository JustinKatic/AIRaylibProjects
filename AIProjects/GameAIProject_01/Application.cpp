#include "Application.h"
#include "raylib.h"
#include "KeyBoardBehaviour.h"
#include "Behaviour.h"
#include "Player.h"


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
	m_player1 = new Player();
	m_player1->SetFriction(1.0f);
	m_player1->SetPosition({ m_windowWidth * 0.25f, m_windowHeight * 0.5f });

}
void Application::Unload()
{
	delete m_player1; m_player1 = nullptr;
}
void Application::Update(float dt)
{
	m_player1->Update(dt);
}
void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	m_player1->Draw();
	EndDrawing();
}

