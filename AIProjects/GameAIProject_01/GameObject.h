#pragma once
#include "raylib.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	//Getters
	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;

	//setters
	void SetPosition(const Vector2& pos);
	void SetVelocity(const Vector2& vel);

protected:

	Vector2 m_position;
	Vector2 m_velocity;

private:

};




