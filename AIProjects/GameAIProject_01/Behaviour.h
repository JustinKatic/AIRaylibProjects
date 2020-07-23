#pragma once

class GameObject;

class Behaviour
{

public:
	Behaviour();
	virtual ~Behaviour();

	virtual void Update(GameObject* obj, float deltaTime);

protected:

private:

};

