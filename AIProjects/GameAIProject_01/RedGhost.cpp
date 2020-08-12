#include"RedGhost.h"
#include"PathFindingBehaviour.h"
#include"FleeBehaviour.h"
#include"Graph2DEditor.h"
#include "Application.h"

RedGhost::RedGhost(Application* app) : GameObject(app)
{


	m_fleeBehaviour = new FleeBehaviour();
	m_fleeBehaviour->SetTargetRadius(100);

	m_pathFindingBehaviour = new PathFindingBehaviour();
	m_pathFindingBehaviour->SetTargetRadius(15);

	SetBehaviour(m_pathFindingBehaviour);

}

RedGhost::~RedGhost()
{
	SetBehaviour(nullptr);

	delete m_fleeBehaviour;
	delete m_pathFindingBehaviour;
}

void RedGhost::Update(float deltaTime)
{


	// get nodes near ourself
	std::vector<Graph2D::Node*> nearbyNodes;
	m_app->GetGraph()->GetNearbyNodes(GetPosition(), 20, nearbyNodes);

	// get nodes near the player
	std::vector<Graph2D::Node*> nearbyGoalNodes;
	m_app->GetGraph()->GetNearbyNodes(m_app->GetPlayer()->GetPosition(), 20, nearbyGoalNodes);
	if (!nearbyNodes.empty() && !nearbyGoalNodes.empty())
	{
		// calculate a path from us to the player
		std::list<Graph2D::Node*> gNodePath;
		m_app->GetGraph()->FindPath(nearbyNodes[0], nearbyGoalNodes[0], gNodePath);
		// create the path as a vector2
		std::vector<Vector2> path;
		for (auto gp : gNodePath)
			path.push_back(gp->data);
		m_pathFindingBehaviour->AddPath(path);
	}


	float distToTarget = Vector2Distance(GetPosition(), m_player->GetPosition());
	if (distToTarget < m_radius)
	{
		DrawText("OUCH", 100, 100, 100, RED);
	}

	GameObject::Update(deltaTime);
}

void RedGhost::Draw()
{
	m_behaviour->Draw(this);
	// Debug Draw
	Vector2 targetHeading = Vector2Add(m_position, m_velocity);
	DrawCircle(m_position.x, m_position.y, 12, RED);
	DrawLine(m_position.x, m_position.y,
		targetHeading.x, targetHeading.y, RED);
}
