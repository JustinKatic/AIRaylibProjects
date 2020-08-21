#include"RedGhost.h"
#include"PathFindingBehaviour.h"
#include"Graph2DEditor.h"
#include "Application.h"
#include "Player.h"
#include <iostream>

RedGhost::RedGhost(Application* app) : GameObject(app)
{

	m_pathFindingBehaviour = new PathFindingBehaviour();
	m_pathFindingBehaviour->SetTargetRadius(40);
	m_pathFindingBehaviour->SetSpeed(350);
	SetBehaviour(m_pathFindingBehaviour);

	redGhostImg = LoadImage("../pacManSprites/RedGhost.png");
	redGhostTex = LoadTextureFromImage(redGhostImg);

	ghostScaredImg = LoadImage("../pacManSprites/GhostScared.png");
	ghostScaredTex = LoadTextureFromImage(ghostScaredImg);
	

	m_pathFindingBehaviour->OnArrive([this]() {
		SetVelocity({ 0,0 });
		});


}

RedGhost::~RedGhost()
{
	SetBehaviour(nullptr);

	delete m_pathFindingBehaviour;
}

void RedGhost::Update(float deltaTime)
{
	m_time += deltaTime;

	float distToTarget = Vector2Distance(GetPosition(), m_player->GetPosition());
	if (distToTarget < m_player->GetCapturedRadius() && m_app->GetPlayer()->GetPowerUpBool() == false)
	{
		m_app->gameOver = true;
	}
	else if (distToTarget < m_player->GetCapturedRadius() && m_app->GetPlayer()->GetPowerUpBool() == true)
	{
		SetPosition({ 9.0f * 33, 9.0f * 33 });
		DrawText("BONUS POINTS", 100, 100, 200, RED);
	}


	if (distToTarget < m_radius && m_app->GetPlayer()->GetPowerUpBool() == true)
	{
		if (m_time > 0.5 && m_behaviour == m_pathFindingBehaviour)
		{
			// get nodes near ourself
			std::vector<Graph2D::Node*> nearbyNodes;
			m_app->GetGraph()->GetNearbyNodes(GetPosition(), 40, nearbyNodes);

			// get nodes near the player
			std::vector<Graph2D::Node*> nearbyGoalNodes;

			m_app->GetGraph()->GetNearbyNodes({ 8.0f * 33, 8.0f * 33 }, 40, nearbyGoalNodes);
			if (!nearbyNodes.empty() && !nearbyGoalNodes.empty())
			{
				// calculate a path from us to the player
				std::list<Graph2D::Node*> gNodePath;
				m_app->GetGraph()->FindPath(nearbyNodes[0], nearbyGoalNodes[0], gNodePath, true);

				// create the path as a vector2
				std::vector<Vector2> path;
				for (auto gp : gNodePath)
				{
					path.push_back(gp->data);
				}

				m_pathFindingBehaviour->AddPath(path);

				m_pathFindingBehaviour->OnArrive([this]() {
					SetVelocity({ 0,0 });
					});
				m_time = 0;

			}
		}
	}
	else
	{
		SetBehaviour(m_pathFindingBehaviour);
	}

	if (m_time > 0.5 && m_behaviour == m_pathFindingBehaviour)
	{
		// get nodes near ourself
		std::vector<Graph2D::Node*> nearbyNodes;
		m_app->GetGraph()->GetNearbyNodes(GetPosition(), 40, nearbyNodes);

		// get nodes near the player
		std::vector<Graph2D::Node*> nearbyGoalNodes;
		m_app->GetGraph()->GetNearbyNodes(m_app->GetPlayer()->GetPosition(), 40, nearbyGoalNodes);

		if (!nearbyNodes.empty() && !nearbyGoalNodes.empty())
		{
			// calculate a path from us to the player
			std::list<Graph2D::Node*> gNodePath;
			m_app->GetGraph()->FindPath(nearbyNodes[0], nearbyGoalNodes[0], gNodePath, false);

			// create the path as a vector2
			std::vector<Vector2> path;
			for (auto gp : gNodePath)
			{
				path.push_back(gp->data);
			}

			m_pathFindingBehaviour->AddPath(path);
			m_time = 0;
		}
	}
	GameObject::Update(deltaTime);
}



void RedGhost::Draw()
{
	m_behaviour->Draw(this);
	// Debug Draw
	Vector2 targetHeading = Vector2Add(m_position, m_velocity);

	float distToTarget = Vector2Distance(GetPosition(), m_player->GetPosition());
	if (distToTarget > m_radius || m_app->GetPlayer()->GetPowerUpBool() == false)
	{
		DrawTexture(redGhostTex, m_position.x - redGhostTex.width / 2, m_position.y - redGhostTex.height / 2, WHITE);
	}
	else
	{
		DrawTexture(ghostScaredTex, m_position.x - ghostScaredTex.width / 2, m_position.y - ghostScaredTex.height / 2, WHITE);
	}
	if (IsKeyDown(KEY_FIVE))
	{
		DrawLine(m_position.x, m_position.y, targetHeading.x, targetHeading.y, RED);
	}
}
