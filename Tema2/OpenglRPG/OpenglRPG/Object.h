#pragma once

#include "Defines.h"
#include "Shape3D.h"

class Object
{
public:
	Object();
	Object(Vec3 position);
	~Object();

	virtual void				Draw();
	virtual void				Update(float dtime);
	virtual void				CheckCollision(Object *object);

	void						SetPosition(Vec3 position);
	virtual void				AddToPosition(Vec3 deltaPosition);
	Vec3						GetPosition();
	Shape3D*					GetCollider();

protected:

	Vec3						m_position;
	Shape3D*					m_collider;
	Mat4						m_model;
};

