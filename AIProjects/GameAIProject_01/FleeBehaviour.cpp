#include "FleeBehaviour.h"
#include "GameObject.h"
#include "Application.h"
FleeBehaviour::FleeBehaviour()
{

}

FleeBehaviour::~FleeBehaviour()
{

}

void FleeBehaviour::Update(GameObject* obj, float deltaTime)
{

	auto& noGo = obj->GetApp()->noGo;

	for (int i = 0; i < 14; i++)
	{
		if (obj->GetPosition().x > noGo[i].pos.x && obj->GetPosition().x < noGo[i].pos.x + noGo[i].size.x &&
			obj->GetPosition().y > noGo[i].pos.y && obj->GetPosition().y < noGo[i].pos.y + noGo[i].size.y)
		{
			Vector2 newVelocity;
			newVelocity.x = obj->GetVelocity().x * -1;
			newVelocity.y = obj->GetVelocity().y * -1;
			obj->SetVelocity(newVelocity);
		}
	}

	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);

	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());
	float m_speed = 400;

	Vector2 dirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));
	Vector2 vecToTarget = Vector2Scale(dirToTarget, m_speed);

	Vector2 targetForcePos = Vector2Add(vecToTarget, obj->GetPosition());
	Vector2 forceDir = Vector2Subtract(heading, targetForcePos);

	if (distToTarget < m_targetRadius)
	{
		obj->ApplyForce(forceDir);
	}
}

void FleeBehaviour::Draw(GameObject* obj)
{
	//DrawCircle(m_target.x, m_target.y, m_targetRadius, RED);
	//DrawCircle(m_target.x, m_target.y, 4, WHITE);
}

const Vector2& FleeBehaviour::GetTarget() const
{
	return m_target;
}

const float& FleeBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void FleeBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

void FleeBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}


