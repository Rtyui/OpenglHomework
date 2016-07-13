#include "VertexFormat.h"


VertexFormat::VertexFormat()
{
	m_position = Vec3(0.f);
	m_normal = Vec3(0.f);
	m_texcoord = Vec2(0.f);
}

VertexFormat::VertexFormat(Vec3 position)
{
	m_position = position;
	m_normal = Vec3(0.f);
	m_texcoord = Vec2(0.f);
}

VertexFormat::VertexFormat(Vec3 position, Vec3 normal)
{
	m_position = position;
	m_normal = normal;
	m_texcoord = Vec2(0.f);
}

VertexFormat::VertexFormat(Vec3 position, Vec2 texcoord)
{
	m_position = position;
	m_normal = Vec3(0.f);
	m_texcoord = texcoord;
}

VertexFormat::VertexFormat(Vec3 position, Vec3 normal, Vec2 texcoord)
{
	m_position = position;
	m_normal = normal;
	m_texcoord = texcoord;
}

VertexFormat::~VertexFormat()
{
}

VertexFormat VertexFormat::operator=(const VertexFormat &vf)
{
	m_position = vf.m_position;
	m_normal = vf.m_normal;
	m_texcoord = vf.m_texcoord;
	return (*this);
}