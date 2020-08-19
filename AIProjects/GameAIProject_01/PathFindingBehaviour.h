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

	const float& GetSpeed() const;
	void SetSpeed(const float& speed);

	void ChangeMode(std::function<void()> callback);


protected:
	Vector2 m_target;
	float m_targetRadius;

	std::vector<Vector2> m_targetNodes;
	
	bool pathAdded = false;

	float m_speed;

	std::function<void()> m_onArriveFunc;

private:


};