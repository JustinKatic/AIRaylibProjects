#include "Player.h"
#include "KeyBoardBehaviour.h"
#include"SeekBehaviour.h"
#include"FleeBehaviour.h"
#include"Graph2DEditor.h"
#include<random>
#include<iostream>


Player::Player(Application* app) : GameObject(app)
{
	m_kbBehaviour = new KeyBoardBehaviour();
	SetEnterRadius(300);
	SetCapturedRadius(80);

	SetBehaviour(m_kbBehaviour);

	PacClosedImg = LoadImage("../pacManSprites/PacClosed.png");
	PacClosedTex = LoadTextureFromImage(PacClosedImg);

	PacHalfImg = LoadImage("../pacManSprites/PacHalfOpen.png");
	PacHalfTex = LoadTextureFromImage(PacHalfImg);

	PacOpenImg = LoadImage("../pacManSprites/PacOpen.png");
	PacOpenTex = LoadTextureFromImage(PacOpenImg);
}

Player::~Player()
{
	SetBehaviour(nullptr);
	delete m_kbBehaviour;
}

void Player::Update(float deltaTime)
{
	if (GetPowerUpBool() == true)
	{
		m_powerUpTimer += deltaTime;
		if (m_powerUpTimer >= 15)
		{
			m_powerUpTimer = 0;
			SetPowerUpBool(false);
		}
	}
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))
	{
		SetBehaviour(m_kbBehaviour);
	}

	m_PacImageChange += deltaTime;

	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	
	GameObject::Draw();
	if (GetPowerUpBool() == false)
	{
		if (m_PacImageChange < 0.25f)
		{
			DrawTexture(PacClosedTex, m_position.x - PacClosedTex.width / 2, m_position.y - PacClosedTex.height / 2, WHITE);
		}
		else if (m_PacImageChange > 0.0f && m_PacImageChange < 0.25f)
		{
			DrawTexture(PacHalfTex, m_position.x - PacHalfTex.width / 2, m_position.y - PacHalfTex.height / 2, WHITE);
		}
		else if (m_PacImageChange > 0.25f && m_PacImageChange < 0.50f)
		{
			DrawTexture(PacOpenTex, m_position.x - PacOpenTex.width / 2, m_position.y - PacOpenTex.height / 2, WHITE);
		}
		else if (m_PacImageChange > 0.50f && m_PacImageChange < 0.75f)
		{
			DrawTexture(PacHalfTex, m_position.x - PacHalfTex.width / 2, m_position.y - PacHalfTex.height / 2, WHITE);
		}
		else
		{
			m_PacImageChange = 0;
		}
	}
	else if (GetPowerUpBool() == true)
	{
		if (m_PacImageChange < 0.25f)
		{
			DrawTexture(PacClosedTex, m_position.x - PacClosedTex.width / 2, m_position.y - PacClosedTex.height / 2, RED);
		}
		else if (m_PacImageChange > 0.25f && m_PacImageChange < 0.5f)
		{
			DrawTexture(PacHalfTex, m_position.x - PacHalfTex.width / 2, m_position.y - PacHalfTex.height / 2, RED);
		}
		else if (m_PacImageChange > 0.5f && m_PacImageChange < 0.75f)
		{
			DrawTexture(PacOpenTex, m_position.x - PacOpenTex.width / 2, m_position.y - PacOpenTex.height / 2, RED);
		}
		else if (m_PacImageChange > 0.75f && m_PacImageChange < 1.0f)
		{
			DrawTexture(PacHalfTex, m_position.x - PacHalfTex.width / 2, m_position.y - PacHalfTex.height / 2, RED);
		}
		else
		{
			m_PacImageChange = 0;
		}
	}
	if (IsKeyDown(KEY_FIVE))
	{
		Vector2 targetHeading = Vector2Add(m_position, m_velocity);
		DrawLine(m_position.x, m_position.y, targetHeading.x, targetHeading.y, RED);

		DrawCircle(GetPosition().x, GetPosition().y, m_enterRadius, { 255,0,0,50 });
		DrawCircle(GetPosition().x, GetPosition().y, m_capturedRadius, { 0,255,0,100 });
	}
}

const bool& Player::GetPowerUpBool() const
{
	return m_powerUp;
}

void Player::SetPowerUpBool(const bool& powerUpBool)
{
	m_powerUp = powerUpBool;
}

const float& Player::GetEnterRadius() const
{
	return m_enterRadius;
}

void Player::SetEnterRadius(const float& radius)
{
	m_enterRadius = radius;
}

const float& Player::GetCapturedRadius() const
{
	return m_capturedRadius;
}

void Player::SetCapturedRadius(const float& radius)
{
	m_capturedRadius = radius;
}

