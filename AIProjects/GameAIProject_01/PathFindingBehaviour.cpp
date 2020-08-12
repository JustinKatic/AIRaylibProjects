#include "PathFindingBehaviour.h"
#include "GameObject.h"
#include "Graph2DEditor.h"
#include <iostream>

PathFindingBehaviour::PathFindingBehaviour()
{

}

PathFindingBehaviour::~PathFindingBehaviour()
{

}

void PathFindingBehaviour::Update(GameObject* obj, float deltaTime)
{


	if (pathAdded == false || m_targetNodes.empty() == true)
	{
		return;
	}

	float distToTarget = Vector2Distance(obj->GetPosition(), m_targetNodes[0]);
	if (distToTarget < m_targetRadius)
	{
		m_targetNodes.erase(m_targetNodes.begin());

		//if (m_onArriveFn)
		//{
		//	m_onArriveFn();
		//}
	}
	if (m_targetNodes.empty() == false)
	{
		Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());
		float headingLen = 200;

		Vector2 dirToTarget = Vector2Normalize(Vector2Subtract(m_targetNodes[0], obj->GetPosition()));
		Vector2 vecToTarget = Vector2Scale(dirToTarget, headingLen);

		Vector2 targetForcePos = Vector2Add(vecToTarget, obj->GetPosition());
		Vector2 forceDir = Vector2Subtract(targetForcePos, heading);

		obj->ApplyForce(forceDir);
	}
}

void PathFindingBehaviour::Draw(GameObject* obj)
{
		if (m_targetNodes.empty() == false && IsKeyDown(KEY_FIVE))		
		{
			DrawCircle(m_targetNodes[0].x, m_targetNodes[0].y, m_targetRadius, RED);
			DrawCircle(m_targetNodes[0].x, m_targetNodes[0].y, 4, WHITE);
		}
}

const Vector2& PathFindingBehaviour::GetTarget() const
{
	return m_target;
}

const float& PathFindingBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void PathFindingBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

void PathFindingBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void PathFindingBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArriveFn = callback;
}

void PathFindingBehaviour::AddPath(std::vector<Vector2>& path)
{
	m_targetNodes = path;
	pathAdded = true;
}

