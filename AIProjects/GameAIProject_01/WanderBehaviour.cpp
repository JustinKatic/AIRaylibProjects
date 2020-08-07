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
	obj->SetFriction(1);

	m_time += deltaTime;
	if (m_time > 0.1)
	{

		if (obj->GetPosition().x < 20 || obj->GetPosition().x > GetScreenWidth() - 20 || obj->GetPosition().y < 20 || obj->GetPosition().y > GetScreenHeight() -20)
		{
			Vector2 newVelocity;
			newVelocity.x = GetScreenWidth() * 0.5f - obj->GetPosition().x;
			newVelocity.y = GetScreenHeight() * 0.5f - obj->GetPosition().y;

			newVelocity = Vector2Normalize(newVelocity);
			newVelocity = Vector2Scale(newVelocity, 20);

			obj->SetVelocity(newVelocity);


		}
		else
		{
			Vector2 defVelocity = { 100.0f, 100.0f };
			if (obj->GetVelocity().x == 0.0f && obj->GetVelocity().y == 0.0f)
			{
				obj->SetVelocity(defVelocity);
			}
			float theta = atan2(obj->GetVelocity().x, obj->GetVelocity().y);
			theta = theta * 57.2958;
			float radius = m_defaultSpeed;
			float finalTheta = (theta - m_offset) + rand() % (2 * m_offset);
			finalTheta = finalTheta * 0.01745;
			Vector2 newVelocity;
			newVelocity.x = radius * sinf(finalTheta);
			newVelocity.y = radius * cosf(finalTheta);
			obj->SetVelocity(newVelocity);
			m_time = 0;
		}
	}

}

void WanderBehaviour::Draw(GameObject* obj)
{

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


