#include"RedGhost.h"
#include"PathFindingBehaviour.h"
#include"FleeBehaviour.h"
#include"Graph2DEditor.h"

RedGhost::RedGhost()
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

	if (IsKeyDown(KEY_TWO))
	{
		m_fleeBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_fleeBehaviour);
	}

	if (m_graph2DEditor && !m_graph2DEditor->m_path.empty() && IsKeyDown(KEY_FOUR))
	{
		//m_pathFindingBehaviour->SetTarget();
		m_pathFindingBehaviour->AddPath(m_graph2DEditor->m_path);
		SetBehaviour(m_pathFindingBehaviour);
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
