#pragma once
#include "GameObject.h"


class WanderBehaviour;
class PathFindingBehaviour;
class Player;

class Graph2DEditor;


class BlueGhost : public GameObject
{
public:
	BlueGhost(Application* app);
	virtual ~BlueGhost();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void SetPlayer(Player* player);

	void SetEditor(Graph2DEditor* editor)
	{
		m_graph2DEditor = editor;
	}



protected:

	WanderBehaviour* m_wanderBehaviour;
	PathFindingBehaviour* m_pathFindingBehaviour;

	Graph2DEditor* m_graph2DEditor = nullptr;

	Player* m_player;



	float m_radius = 300.0f;

	float m_time = 0.0f; 



private:
	//BlueGhostImage
	Image BlueGhostImg;
	Texture2D BlueGhostTex;

	Image ghostScaredImg;
	Texture2D ghostScaredTex;
};