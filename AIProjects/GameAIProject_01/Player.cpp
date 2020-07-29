#include "Player.h"
#include "KeyBoardBehaviour.h"
#include"SeekBehaviour.h"
#include"FleeBehaviour.h"
#include"WanderBehaviour.h"
#include<iostream>

Player::Player()
{
	m_kbBehaviour = new KeyBoardBehaviour();
	

	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->SetTargetRadius(25);
	m_seekBehaviour->OnArrive([this]()
		{
			SetVelocity({ 0, 0 });
			SetBehaviour(m_kbBehaviour);
		});


	m_fleeBehaviour = new FleeBehaviour();
	m_fleeBehaviour->SetTargetRadius(100);

	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->OnArrive([this]()
		{
			SetBehaviour(m_wanderBehaviour);
		});

	SetBehaviour(m_kbBehaviour);



}

Player::~Player()
{
	SetBehaviour(nullptr);
	delete m_kbBehaviour;
	delete m_seekBehaviour;
	delete m_fleeBehaviour;
}

void Player::Update(float deltaTime)
{
	if (IsKeyDown(KEY_S))
	{
		m_seekBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_seekBehaviour);
	}
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))
	{
		SetBehaviour(m_kbBehaviour);
	}
	if (IsKeyDown(KEY_F))
	{
		m_fleeBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_fleeBehaviour);	
	}
	if (IsKeyDown(KEY_W))
	{
		m_wanderBehaviour->SetTarget({/*add vector 2 of where target needs to move to*/});
		SetBehaviour(m_wanderBehaviour);
	}
	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}
