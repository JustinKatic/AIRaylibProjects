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
	

	void OnArrive(std::function<void()> callback);

protected:
	Vector2 m_target;
	float m_targetRadius = 1.0f;

	std::function<void()> m_onArriveFn;

private:


};

