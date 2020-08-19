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
	}
	if (m_targetNodes.empty() == false)
	{
		Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());

		Vector2 dirToTarget = Vector2Normalize(Vector2Subtract(m_targetNodes[0], obj->GetPosition()));
		Vector2 vecToTarget = Vector2Scale(dirToTarget, GetSpeed());

		Vector2 targetForcePos = Vector2Add(vecToTarget, obj->GetPosition());
		Vector2 forceDir = Vector2Subtract(targetForcePos, heading);

		obj->ApplyForce(forceDir);
	}
	else
	{
		if (m_onArriveFunc)
			m_onArriveFunc();
	}
}

void PathFindingBehaviour::Draw(GameObject* obj)
{
	if (m_targetNodes.empty() == false && IsKeyDown(KEY_FIVE))
	{
		DrawCircle(m_targetNodes[0].x, m_targetNodes[0].y, m_targetRadius, {255,0,0,100});
		DrawCircle(m_targetNodes[0].x, m_targetNodes[0].y, 4, WHITE);

		if (!m_targetNodes.empty())
		{
			for (int i = 0; i < m_targetNodes.size() - 1; i++)
			{
				DrawLineEx(m_targetNodes[i], m_targetNodes[i + 1], 5, GREEN);
			}
		}
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


void PathFindingBehaviour::AddPath(std::vector<Vector2>& path)
{
	m_targetNodes = path;
	pathAdded = true;
}

const float& PathFindingBehaviour::GetSpeed() const
{
	return m_speed;
}

void PathFindingBehaviour::SetSpeed(const float& speed)
{
	m_speed = speed;
}

void PathFindingBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArriveFunc = callback;
}

