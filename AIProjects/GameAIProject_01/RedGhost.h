#pragma once
#include "GameObject.h"


class PathFindingBehaviour;
class Graph2DEditor;
class Player;

class RedGhost : public GameObject
{
public:
	RedGhost(Application* app);
	virtual ~RedGhost();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void SetEditor(Graph2DEditor* editor)
	{
		m_graph2DEditor = editor;
	}

	void SetPlayer(Player* player)
	{
		m_player = player;
	}


protected:

	PathFindingBehaviour* m_pathFindingBehaviour;
	Graph2DEditor* m_graph2DEditor = nullptr;

	Player* m_player;

	float m_radius = 300.0f;

	float m_time = 0.0f;



private:
	//redGhostImage
	Image redGhostImg;
	Texture2D redGhostTex;

	Image ghostScaredImg;
	Texture2D ghostScaredTex;
};