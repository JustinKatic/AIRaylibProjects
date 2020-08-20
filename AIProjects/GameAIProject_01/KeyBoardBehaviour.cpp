
#include "KeyBoardBehaviour.h"
#include "GameObject.h"
#include "raylib.h"
#include <iostream>
#include "Application.h"

KeyBoardBehaviour::KeyBoardBehaviour() : Behaviour()
{
	m_upKey = KEY_W;
	m_downKey = KEY_S;
	m_leftKey = KEY_A;
	m_rightKey = KEY_D;
	m_moveForce = 200;
}

KeyBoardBehaviour::KeyBoardBehaviour(int upKey, int downKey, int leftKey, int rightKey, float moveForce) :
	Behaviour(),
	m_upKey(upKey),
	m_downKey(downKey),
	m_leftKey(leftKey),
	m_rightKey(rightKey),
	m_moveForce(moveForce)
{

}

KeyBoardBehaviour::~KeyBoardBehaviour()
{

}

void KeyBoardBehaviour::Update(GameObject* obj, float deltaTime)
{

	//collision for keyboard behaviour if inside collision reverse velocity
	auto& noGo = obj->GetApp()->noGo;
	for (int i = 0; i < 17; i++)
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

	//if key is down move in direction
	if (IsKeyDown(m_leftKey)) obj->ApplyForce({ -m_moveForce, 0 });
	if (IsKeyDown(m_rightKey)) obj->ApplyForce({ m_moveForce, 0 });
	if (IsKeyDown(m_upKey)) obj->ApplyForce({ 0,  -m_moveForce });
	if (IsKeyDown(m_downKey)) obj->ApplyForce({ 0,   m_moveForce });
}

