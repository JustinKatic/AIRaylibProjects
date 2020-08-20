#include "SeekBehaviour.h"
#include <iostream>
#include "GameObject.h"

SeekBehaviour::SeekBehaviour()
{

}

SeekBehaviour::~SeekBehaviour()
{

}

void SeekBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);
	//if entity reached target call on arrive function
	if (distToTarget < m_targetRadius)
	{
		if (m_onArriveFn)
		{
			m_onArriveFn();
		}
	}
	//add force in direction of target
	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());
	float headingLen = 400;

	Vector2 dirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));
	Vector2 vecToTarget = Vector2Scale(dirToTarget, headingLen);

	Vector2 targetForcePos = Vector2Add(vecToTarget, obj->GetPosition());
	Vector2 forceDir = Vector2Subtract(targetForcePos, heading);

	obj->ApplyForce(forceDir);
}

void SeekBehaviour::Draw(GameObject* obj)
{
	//DEBUG DRAW
	DrawCircle(m_target.x, m_target.y, m_targetRadius, RED);
	DrawCircle(m_target.x, m_target.y, 4, WHITE);
}

const Vector2& SeekBehaviour::GetTarget() const
{
	return m_target;
}

const float& SeekBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

void SeekBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void SeekBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArriveFn = callback;
}
