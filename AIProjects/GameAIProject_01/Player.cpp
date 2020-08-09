#include "Player.h"
#include "KeyBoardBehaviour.h"
#include"SeekBehaviour.h"
#include"FleeBehaviour.h"
#include"WanderBehaviour.h"
#include"PathFindingBehaviour.h"
#include"Graph2DEditor.h"
#include<random>
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

	m_pathFindingBehaviour = new PathFindingBehaviour();
	m_pathFindingBehaviour->SetTargetRadius(15);
	m_pathFindingBehaviour->OnArrive([this]()
		{
			SetBehaviour(m_pathFindingBehaviour);
		});

	SetBehaviour(m_kbBehaviour);

}

Player::~Player()
{
	SetBehaviour(nullptr);
	delete m_kbBehaviour;
	delete m_seekBehaviour;
	delete m_fleeBehaviour;
	delete m_wanderBehaviour;
}

void Player::Update(float deltaTime)
{
	if (IsKeyDown(KEY_ONE))
	{
		m_seekBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_seekBehaviour);
	}
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))
	{
		SetBehaviour(m_kbBehaviour);
	}
	if (IsKeyDown(KEY_TWO))
	{
		m_fleeBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_fleeBehaviour);
	}
	if (IsKeyDown(KEY_THREE))
	{
		SetBehaviour(m_wanderBehaviour);
	}
	if (m_graph2DEditor && !m_graph2DEditor->m_path.empty() && IsKeyDown(KEY_FOUR))
	{
		//m_pathFindingBehaviour->SetTarget();
		m_pathFindingBehaviour->AddPath(m_graph2DEditor->m_path);
		SetBehaviour(m_pathFindingBehaviour);
	}
	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}
