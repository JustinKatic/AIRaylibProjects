#include "WanderBehaviour.h"
#include"GameObject.h"
#include <time.h>
#include <iostream>
#include"Application.h"

WanderBehaviour::WanderBehaviour()
{

}

WanderBehaviour::~WanderBehaviour()
{

}

void WanderBehaviour::Update(GameObject* obj, float deltaTime)
{
	obj->SetFriction(1);

	auto& noGo = obj->GetApp()->noGo;

	for (int i = 0; i < 16; i++)
	{
		if (obj->GetPosition().x > noGo[i].pos.x && obj->GetPosition().x < noGo[i].pos.x + noGo[i].size.x &&
			obj->GetPosition().y > noGo[i].pos.y && obj->GetPosition().y < noGo[i].pos.y + noGo[i].size.y)
		{
			Vector2 newVelocity;
			obj->SetFriction(-10);
			newVelocity.x = obj->GetVelocity().x * -1;
			newVelocity.y = obj->GetVelocity().y * -1;
			obj->SetVelocity(newVelocity);
		}
	}

	m_time += deltaTime;
	if (m_time > 0.1)
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

void WanderBehaviour::Draw(GameObject* obj)
{

}


