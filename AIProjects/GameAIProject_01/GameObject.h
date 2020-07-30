#pragma once
#include "raymath.h"

class Behaviour;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    virtual void Update(float deltaTime);
    virtual void Draw();
    // Getters
    const Vector2& GetPosition() const;
    const Vector2& GetVelocity() const;
    const float& GetFriction() const;
    Behaviour* GetBehaviour() const;

    // setters
    void SetPosition(const Vector2& pos);
    void SetVelocity(const Vector2& vel);
    void SetFriction(const float& friction);
    void SetBehaviour(Behaviour* behaviour);


    void ApplyForce(const Vector2& force);
    
protected:
    Vector2 m_position = { 0, 0 };
    Vector2 m_velocity = { 0, 0 };
    Vector2 m_acceleration = { 0, 0 };
    float m_friction = 0.0f;
    Behaviour* m_behaviour;

    Vector2 m_direction;




private:
};




