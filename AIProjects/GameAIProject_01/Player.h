#pragma once
#include "GameObject.h"


class KeyBoardBehaviour;
class Application;

class Player : public GameObject
{
public:
	Player(Application* app);
	virtual ~Player();

	virtual void Update(float deltaTime);
	virtual void Draw();

	const bool& GetPowerUpBool() const;
	void SetPowerUpBool(const bool& powerUpBool);


	const float& GetEnterRadius() const;
	void SetEnterRadius(const float& radius);

	const float& GetCapturedRadius() const;
	void SetCapturedRadius(const float& radius);
	

protected:
	KeyBoardBehaviour* m_kbBehaviour;

	float m_enterRadius;
	float m_capturedRadius;

	bool m_powerUp = false;
	float m_powerUpTimer = 0.0f;

	float m_PacImageChange = 0.0f;



private:

	//PacClosedImage
	Image PacClosedImg;
	Texture2D PacClosedTex;
	//PaxHalfImage
	Image PacHalfImg;
	Texture2D PacHalfTex;
	//PacOpenImage
	Image PacOpenImg;
	Texture2D PacOpenTex;

	

};

