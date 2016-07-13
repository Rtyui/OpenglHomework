#pragma once

#include "Defines.h"

class Camera
{
public:

	enum TYPE {FPC, TPC};
	Camera();
	Camera(TYPE t);
	~Camera();

	void					Update(float dtime);

	void					LoadMatrices();

	void					SetForward(Vec3 forward);
	Vec3					GetForward();

	void					SetRight(Vec3 right);
	Vec3					GetRight();

	void					AddToPosition(Vec3 deltaPosition);
	void					SetPosition(Vec3 position);
	void					RequireRotateY(float angle);

	bool					IsRotating();

	void					SetViewport();

private:

	void					RotateY(float angle);

	TYPE					m_type;

	Vec3					m_position;
	Vec3					m_forward;
	Vec3					m_up;
	Vec3					m_right;

	bool					m_rotating;

	float					m_rotatingTime;
	float					m_currentRotatingAngle;
};