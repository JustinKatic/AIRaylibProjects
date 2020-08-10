#pragma once
#include "Behaviour.h"
#include "raylib.h"
#include <vector>
#include <functional>

class Graph2DEditor;

class PathFindingBehaviour : public Behaviour
{
public:

	PathFindingBehaviour();
	virtual ~PathFindingBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);


	const Vector2& GetTarget() const;
	const float& GetTargetRadius() const;


	void SetTarget(const Vector2& target);
	void SetTargetRadius(const float& radius);

	void OnArrive(std::function<void()> callback);

	void AddPath(std::vector<Vector2>& path);




protected:
	Vector2 m_target;
	float m_targetRadius;

	std::vector<Vector2> m_targetNodes;
	
	std::function<void()> m_onArriveFn;
	bool pathAdded = false;
	//Graph2DEditor* m_graph2DEditor;

private:


};