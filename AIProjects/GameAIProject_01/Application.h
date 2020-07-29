#pragma once
#include "GameObject.h"

class Graph2D;
class Graph2DEditor;

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
	int m_windowWidth;
	int m_windowHeight;

	//===============================================================================================================
	/*Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;*/
	//===============================================================================================================


};