#pragma once
#include "GameObject.h"


class Application
{
public:

	Application(int windowWidth, int windowHeight);
	~Application();

	void Run();

	void Update(float deltaTime);
	void Draw();

	void Load();
	void Unload();

private:
	GameObject* m_player1 = nullptr;
	GameObject* m_player2 = nullptr;
	int m_windowWidth;
	int m_windowHeight;


};