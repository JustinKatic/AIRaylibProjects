#include "GameObject.h"
#include"Behaviour.h";
GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}
void GameObject::Update(float deltaTime)
{
	m_behaviour->Update(this, deltaTime);

	// ApplyForce( -m_velocity * m_friction );
	ApplyForce(Vector2Scale(Vector2Negate(m_velocity), m_friction));
	// m_velocity += m_acceleration * deltaTime;
	m_velocity = Vector2Add(m_velocity, Vector2Scale(m_acceleration, deltaTime));
	// m_position += m_velocity * deltaTime;
	m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime));
	// clear the acceleration
	m_acceleration = Vector2Zero();

}
void GameObject::Draw()
{
	m_behaviour->Draw(this);
	// Debug Draw
	Vector2 targetHeading = Vector2Add(m_position, m_velocity);
	DrawCircle(m_position.x, m_position.y, 12, YELLOW);
	DrawLine(m_position.x, m_position.y,
		targetHeading.x, targetHeading.y, RED);
}
void GameObject::ApplyForce(const Vector2& force)
{
	// m_acceleration += force
	m_acceleration = Vector2Add(m_acceleration, force);
}
const Vector2& GameObject::GetPosition() const
{
	return m_position;
}
const Vector2& GameObject::GetVelocity() const
{
	return m_velocity;
}
const float& GameObject::GetFriction() const
{
	return m_friction;
}
Behaviour* GameObject::GetBehaviour() const
{
	return m_behaviour;
}
void GameObject::SetPosition(const Vector2& pos)
{
	m_position = pos;
}
void GameObject::SetVelocity(const Vector2& vel)
{
	m_velocity = vel;
}
void GameObject::SetFriction(const float& friction)
{
	m_friction = friction;
}

void GameObject::SetBehaviour(Behaviour* behaviour)
{
	m_behaviour = behaviour;
}
