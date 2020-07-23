#include "Application.h"
#include "raylib.h"
#include "KeyBoardBehaviour.h"
#include "Behaviour.h"


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
	auto kb1 = new KeyBoardBehaviour();
	kb1->SetKeys(KEY_W, KEY_S, KEY_A, KEY_D);

	auto kb2 = new KeyBoardBehaviour();
	kb2->SetKeys(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);

	m_player1 = new GameObject();
	m_player1->SetFriction(1.0f);
	m_player1->SetPosition({ m_windowWidth * 0.25f, m_windowHeight * 0.5f });
	m_player1->SetBehaviour(kb1);

	m_player2 = new GameObject();
	m_player2->SetFriction(1.0f);
	m_player2->SetPosition({ m_windowWidth * 0.75f, m_windowHeight * 0.5f });
	m_player2->SetBehaviour(kb2);
}
void Application::Unload()
{
	delete m_player1; m_player1 = nullptr;
	delete m_player2; m_player2 = nullptr;
}
void Application::Update(float dt)
{
	m_player1->Update(dt);
	m_player2->Update(dt);
}
void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	m_player1->Draw();
	m_player2->Draw();
	EndDrawing();
}

