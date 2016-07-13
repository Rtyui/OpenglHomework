#pragma once

#include "Object.h"

class Platform : public Object
{
public:
	Platform();
	Platform(Vec3 position, float side, bool finish);
	~Platform();

	virtual void				Draw() override;

	bool						IsFinish();

private:

	bool						m_finish;
};

