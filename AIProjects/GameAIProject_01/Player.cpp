#include "Player.h"
#include "KeyBoardBehaviour.h"
#include"SeekBehaviour.h"

Player::Player()
{
	m_kbBehaviour = new KeyBoardBehaviour();
	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->SetTargetRadius(25);
	m_seekBehaviour->OnArrive([this]()
		{
			SetBehaviour(m_kbBehaviour);
		});

	SetBehaviour(m_kbBehaviour);
}

Player::~Player()
{
	SetBehaviour(nullptr);
	delete m_kbBehaviour;
	delete m_seekBehaviour;
}

void Player::Update(float deltaTime)
{
	if (IsMouseButtonPressed(0))
	{
		m_seekBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_seekBehaviour);
	}


	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}
