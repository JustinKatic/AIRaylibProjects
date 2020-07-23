
#include "KeyBoardBehaviour.h"
#include "GameObject.h"
#include "raylib.h"

KeyBoardBehaviour::KeyBoardBehaviour()
{

}

KeyBoardBehaviour::~KeyBoardBehaviour()
{

}

void KeyBoardBehaviour::Update(GameObject* obj, float deltaTime)
{
	if (IsKeyDown(m_leftKey)) obj->ApplyForce({ -200, 0 });
	if (IsKeyDown(m_rightKey)) obj->ApplyForce({ 200, 0 });
	if (IsKeyDown(m_upKey)) obj->ApplyForce({ 0,  -200 });
	if (IsKeyDown(m_downKey)) obj->ApplyForce({ 0,   200 });
}

void KeyBoardBehaviour::SetKeys(int up, int down, int left, int right)
{
	m_upKey = up;
	m_downKey = down;
	m_leftKey = left;
	m_rightKey = right;
}
