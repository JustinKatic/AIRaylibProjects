#pragma once
#include "GameObject.h"


class PathFindingBehaviour;
class FleeBehaviour;
class Graph2DEditor;

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


protected:

	PathFindingBehaviour* m_pathFindingBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	Graph2DEditor* m_graph2DEditor = nullptr;



private:

};