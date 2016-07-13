#pragma once

#include "Defines.h"

class VertexFormat
{
public:
	VertexFormat();
	VertexFormat(Vec3 position);
	VertexFormat(Vec3 position, Vec3 normal);
	VertexFormat(Vec3 position, Vec2 texcoord);
	VertexFormat(Vec3 position, Vec3 normal, Vec2 texcoord);

	~VertexFormat();

	VertexFormat operator=(const VertexFormat &vf);



private:

	Vec3				m_position;
	Vec3				m_normal;
	Vec2				m_texcoord;
};

