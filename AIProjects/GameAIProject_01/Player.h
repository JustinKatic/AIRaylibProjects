#pragma once
#include "GameObject.h"
#include <vector>


class KeyBoardBehaviour;
class SeekBehaviour;
class FleeBehaviour;
class WanderBehaviour;
class PathFindingBehaviour;
class Graph2DEditor;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void SetEditor(Graph2DEditor* editor)
	{
		m_graph2DEditor = editor;
	}


protected:
	KeyBoardBehaviour* m_kbBehaviour;
	SeekBehaviour* m_seekBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	WanderBehaviour* m_wanderBehaviour;
	PathFindingBehaviour* m_pathFindingBehaviour;
	Graph2DEditor* m_graph2DEditor = nullptr;
	

	
	


private:

};

