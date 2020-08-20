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
	//gets refrence to collision boxes and stored them insode of nogo to save typeing the whole line each time
	auto& noGo = obj->GetApp()->noGo;

	//collision checks that reverse the velocity of entities when entitity has entered the bounds of noGO[]
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

	// implementing force away from m_target position
	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);
	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());
	float m_speed = 400;
	Vector2 dirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));
	Vector2 vecToTarget = Vector2Scale(dirToTarget, m_speed);
	Vector2 targetForcePos = Vector2Add(vecToTarget, obj->GetPosition());
	Vector2 forceDir = Vector2Subtract(heading, targetForcePos);

	//applying the flee force added if entity is within the raidus
	if (distToTarget < m_targetRadius)
	{
		obj->ApplyForce(forceDir);
	}
}

void FleeBehaviour::Draw(GameObject* obj)
{
	//debug circles for where the flee target is
	DrawCircle(m_target.x, m_target.y, m_targetRadius, RED);
	DrawCircle(m_target.x, m_target.y, 4, WHITE);
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


