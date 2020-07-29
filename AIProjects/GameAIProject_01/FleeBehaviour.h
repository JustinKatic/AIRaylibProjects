#pragma once
#include "Behaviour.h"
#include "raylib.h"


class FleeBehaviour : public Behaviour
{
public:

	FleeBehaviour();
	virtual ~FleeBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);


	const Vector2& GetTarget() const;
	const float& GetTargetRadius() const;


	void SetTarget(const Vector2& target);
	void SetTargetRadius(const float& radius);


protected:
	Vector2 m_target;
	float m_targetRadius = 1.0f;

private:
};

