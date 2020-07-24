#pragma once
#include "Behaviour.h"

class KeyBoardBehaviour : public Behaviour
{

public:
	KeyBoardBehaviour();
	KeyBoardBehaviour(int upKey, int downKey, int leftKey, int rightKey, float moveForce);
	virtual ~KeyBoardBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);


protected:

	int m_upKey;
	int m_downKey;
	int m_rightKey;
	int m_leftKey;
	float m_moveForce;

private:

};

