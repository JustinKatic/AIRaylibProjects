#include "WanderBehaviour.h"
#include"GameObject.h"
#include <time.h>
#include <iostream>

WanderBehaviour::WanderBehaviour()
{

}

WanderBehaviour::~WanderBehaviour()
{

}

void WanderBehaviour::Update(GameObject* obj, float deltaTime)
{
	float rAngle = (float)(rand() % 360) * 0.0174f;
	//float radius = GetTargetRadius();

	Vector2 defaultVelocity = { 100.0f, 100.0f };

	if (obj->GetVelocity().x == 0.0f && obj->GetVelocity().y == 0.0f)
	{
		obj->SetVelocity(defaultVelocity);
	}

	Vector2 circleCentre = Vector2Add(Vector2Scale(Vector2Normalize(obj->GetVelocity()), 200.0f), obj->GetPosition());

	m_target.x = GetTargetRadius() * cosf(rAngle) + circleCentre.x;
	m_target.y = -GetTargetRadius() * sinf(rAngle) + circleCentre.y;

	Vector2 forceDir = Vector2Subtract(m_target, circleCentre);

	obj->ApplyForce(forceDir);


}

void WanderBehaviour::Draw(GameObject* obj)
{
	DrawCircle(m_target.x, m_target.y, m_targetRadius, LIGHTGRAY);
	DrawCircle(m_target.x, m_target.y, 4, GRAY);
}

const Vector2& WanderBehaviour::GetTarget() const
{
	return m_target;
}

const float& WanderBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}


void WanderBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

void WanderBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}


