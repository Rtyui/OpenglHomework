#pragma once

#include "Object.h"
#include "Camera.h"

class Player : public Object
{
public:
	Player();
	Player(Vec3 position, Camera* tpc, Camera* fpc);
	~Player();

	virtual void				Update(float dtime) override;
	virtual void				Draw() override;
	virtual void				CheckCollision(Object *object) override;
	virtual void				AddToPosition(Vec3 deltaPosition) override;

private:

	Camera*						m_tpc;
	Camera*						m_fpc;
	float						m_jumpVelocity;
	float						m_gravityAccel;
	bool						m_jumping;
	bool						m_ableToJump;
};

