#include "Platform.h"
#include "Cube.h"

Platform::Platform()
{
}

Platform::Platform(Vec3 position, float side, bool finish) :
Object(position)
{
	m_finish = finish;

	if (m_finish)
	{
		m_collider = new Cube(side, Vec3(0.f, 1.f, 0.f));
	}
	else
	{
		m_collider = new Cube(side);
	}
}

Platform::~Platform()
{
}

void Platform::Draw()
{
	Object::Draw();
}

bool Platform::IsFinish()
{
	return m_finish;
}
