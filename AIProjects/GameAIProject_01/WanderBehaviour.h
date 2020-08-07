#pragma once
#include "Behaviour.h"
#include "raylib.h"

#include <functional>

class WanderBehaviour : public Behaviour
{
public:

	WanderBehaviour();
	virtual ~WanderBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);


	const Vector2& GetTarget() const;
	const float& GetTargetRadius() const;

	void SetTarget(const Vector2& target);
	void SetTargetRadius(const float& radius);


protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;
	float m_time = 0;
	float m_defaultSpeed = 100;
	int m_offset = 40;


private:


};

