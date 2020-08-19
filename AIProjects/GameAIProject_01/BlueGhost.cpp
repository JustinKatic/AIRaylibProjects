#include"BlueGhost.h"
#include"WanderBehaviour.h"
#include"PathFindingBehaviour.h"
#include"Graph2DEditor.h"
#include "Application.h"
#include "Player.h"

BlueGhost::BlueGhost(Application* app) : GameObject(app)
{
	m_wanderBehaviour = new WanderBehaviour();

	m_pathFindingBehaviour = new PathFindingBehaviour();
	m_pathFindingBehaviour->SetTargetRadius(40);

	m_pathFindingBehaviour->OnArrive([this]() {
		SetVelocity({ 0,0 });
		});


	SetBehaviour(m_wanderBehaviour);

	BlueGhostImg = LoadImage("../pacManSprites/BlueGhost.png");
	BlueGhostTex = LoadTextureFromImage(BlueGhostImg);

	ghostScaredImg = LoadImage("../pacManSprites/GhostScared.png");
	ghostScaredTex = LoadTextureFromImage(ghostScaredImg);
}

BlueGhost::~BlueGhost()
{
	SetBehaviour(nullptr);
	delete m_wanderBehaviour;
}

void BlueGhost::Update(float deltaTime)
{
	m_time += deltaTime;

	float distToTarget = Vector2Distance(GetPosition(), m_player->GetPosition());

	if (distToTarget < m_player->GetCapturedRadius() && m_app->GetPlayer()->GetPowerUpBool() == true)
	{
		SetPosition({ 9.0f * 33, 9.0f * 33 });
		m_app->m_score += 50;
	}
	else if (distToTarget < m_player->GetCapturedRadius() && m_app->GetPlayer()->GetPowerUpBool() == false)
	{
		SetVelocity({ 0, 0 });
		m_app->gameOver = true;
	}

	//FLEE BEHAVIOUR
	if (distToTarget < m_radius && m_app->GetPlayer()->GetPowerUpBool() == true)
	{
		m_pathFindingBehaviour->SetSpeed(350);
		SetBehaviour(m_pathFindingBehaviour);

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

	//PATH FIND BEHAVIOUR
	else if (distToTarget < m_radius && m_app->GetPlayer()->GetPowerUpBool() == false)
	{
		m_pathFindingBehaviour->SetSpeed(400);
		SetBehaviour(m_pathFindingBehaviour);
		if (m_time > 0.5 && m_behaviour == m_pathFindingBehaviour)
		{
			// get nodes near ourself
			std::vector<Graph2D::Node*> nearbyNodes;
			m_app->GetGraph()->GetNearbyNodes(GetPosition(), 40, nearbyNodes);

			// get nodes near the player
			std::vector<Graph2D::Node*> nearbyGoalNodes;
			m_app->GetGraph()->GetNearbyNodes(m_app->GetPlayer()->GetPosition(), 20, nearbyGoalNodes);
			if (!nearbyNodes.empty() && !nearbyGoalNodes.empty())
			{
				// calculate a path from us to the player
				std::list<Graph2D::Node*> gNodePath;
				m_app->GetGraph()->FindPath(nearbyNodes[0], nearbyGoalNodes[0], gNodePath, true);
				// create the path as a vector2
				std::vector<Vector2> path;

				for (auto gp : gNodePath)
					path.push_back(gp->data);
				m_pathFindingBehaviour->AddPath(path);
				m_time = 0;
			}
		}
	}

	else
	{
		SetBehaviour(m_wanderBehaviour);
	}

	GameObject::Update(deltaTime);
}

void BlueGhost::Draw()
{
	m_behaviour->Draw(this);
	// Debug Draw
	Vector2 targetHeading = Vector2Add(m_position, m_velocity);

	float distToTarget = Vector2Distance(GetPosition(), m_player->GetPosition());
	if (distToTarget > m_radius || m_app->GetPlayer()->GetPowerUpBool() == false)
	{
		DrawTexture(BlueGhostTex, m_position.x - BlueGhostTex.width / 2, m_position.y - BlueGhostTex.width / 2, WHITE);
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

void BlueGhost::SetPlayer(Player* player)
{
	m_player = player;
}
