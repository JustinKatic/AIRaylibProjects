#pragma once
#include "Behaviour.h"

class KeyBoardBehaviour : public Behaviour
{

public:
	KeyBoardBehaviour();
	virtual ~KeyBoardBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);

	void SetKeys(int up, int down, int left, int right);

protected:

	int m_upKey;
	int m_downKey;
	int m_rightKey;
	int m_leftKey;

private:

};

