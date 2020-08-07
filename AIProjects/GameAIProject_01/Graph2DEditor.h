#pragma once
#include "Graph2D.h"

	class Graph2D;

class Graph2DEditor
{
public:

	Graph2DEditor();
	~Graph2DEditor();

	void Update(float deltaTime);
	void Draw();
	
	Graph2D* GetGraph();
	void SetGraph(Graph2D* graph);

	const float GetConnectionRadius() const;
	void SetConnectionRadius(float radius);

protected:
	Graph2D* m_graph;

	Graph2D::Node* m_startNode;
	Graph2D::Node* m_endNode;

	float m_connectionRadius = 60.0f;
	bool m_endNodeFound = false;

	std::vector<Vector2> m_path;

private:

};

