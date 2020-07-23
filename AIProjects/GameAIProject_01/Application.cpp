#include "Application.h"
#include "raylib.h"


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


	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		Update(dt);
		Draw();
	}

	CloseWindow();
}

//use to update functionality every frame
void Application::Update(float deltaTime)
{

}
//use to draw to screen every frame
void Application::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	EndDrawing();
}

