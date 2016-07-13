#include "RectangleShape.h"


RectangleShape::RectangleShape()
{
}

RectangleShape::RectangleShape(glm::vec2 center, glm::vec2 size, glm::vec3 color, lab::BlackBox* blackBox) :
Shape(center, color, blackBox),
m_size(size)
{
	LoadMesh();
}

RectangleShape::~RectangleShape()
{
}

void RectangleShape::LoadMesh()
{
	std::vector<MyVertexFormat> vertecsi;
	std::vector<glm::uvec3> indecsi;

	vertecsi.push_back(MyVertexFormat(m_center.x - m_size.x / 2.f, m_center.y - m_size.y / 2.f));
	vertecsi.push_back(MyVertexFormat(m_center.x - m_size.x / 2.f, m_center.y + m_size.y / 2.f));
	vertecsi.push_back(MyVertexFormat(m_center.x + m_size.x / 2.f, m_center.y + m_size.y / 2.f));
	vertecsi.push_back(MyVertexFormat(m_center.x + m_size.x / 2.f, m_center.y - m_size.y / 2.f));

	indecsi.push_back(glm::uvec3(0, 1, 2));
	indecsi.push_back(glm::uvec3(0, 2, 3));

	//creaza vao
	unsigned int mesh_vao;
	glGenVertexArrays(1, &mesh_vao);
	glBindVertexArray(mesh_vao);

	//creeaza vbo
	unsigned int mesh_vbo;
	glGenBuffers(1, &mesh_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*vertecsi.size(), &vertecsi[0], GL_STATIC_DRAW);

	//creeaza ibo
	unsigned int mesh_ibo;
	glGenBuffers(1, &mesh_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indecsi.size() * 3, &indecsi[0], GL_STATIC_DRAW);

	//creez obiect de tip mesh
	m_mesh = new lab::Mesh(mesh_vbo, mesh_ibo, mesh_vao, indecsi.size() * 3);

	// traducem la OpenGL cum sa foloseasca datele noastre
	m_blackBox->bindMesh(m_mesh, sizeof(MyVertexFormat));

	m_mesh->setColor(m_color.x, m_color.y, m_color.z);
}

bool RectangleShape::CheckIntersect(glm::vec2 point1, glm::vec2 point2, float &angle, glm::vec3& color, glm::vec2& nextPos)
{
	float x1 = point1.x, y1 = point1.y, x2 = point2.x, y2 = point2.y; //line 1
	bool collides = false;

	if (point1.y > m_center.y + m_size.y / 2.f)
	{
		if (CheckIntersectUp(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectDown(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectLeft(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectRight(x1, y1, x2, y2, angle, nextPos)) collides = true;
	}
	else if (point1.y < m_center.y - m_size.y / 2.f)
	{
		if (CheckIntersectDown(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectUp(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectLeft(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectRight(x1, y1, x2, y2, angle, nextPos)) collides = true;
	}
	else if (point1.x > m_center.x + m_size.x / 2.f)
	{
		if (CheckIntersectRight(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectLeft(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectUp(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectDown(x1, y1, x2, y2, angle, nextPos)) collides = true;
	}
	else if (point1.x < m_center.x - m_size.x / 2.f)
	{
		if (CheckIntersectLeft(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectRight(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectUp(x1, y1, x2, y2, angle, nextPos)) collides = true;
		else if (CheckIntersectDown(x1, y1, x2, y2, angle, nextPos)) collides = true;
	}

	if (collides)
	{
		color = (color + m_color) / 2.f;
	}
	return collides;
}

bool RectangleShape::CheckIntersectDown(float x1, float y1, float x2, float y2, float &angle, glm::vec2& nextPos)
{
	float x3 = m_center.x - m_size.x / 2.f,
		  y3 = m_center.y - m_size.y / 2.f,
		  x4 = m_center.x + m_size.x / 2.f,
		  y4 = m_center.y - m_size.y / 2.f;

	float d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
	if (d == 0) return false;

	float xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
	float yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

	if (xi < glm::min(x1, x2) - COLLISION_ERROR || xi >glm::max(x1, x2) + COLLISION_ERROR) return false;
	if (xi < glm::min(x3, x4) - COLLISION_ERROR || xi >glm::max(x3, x4) + COLLISION_ERROR) return false;

	if (yi < glm::min(y1, y2) - COLLISION_ERROR || yi >glm::max(y1, y2) + COLLISION_ERROR) return false;
	if (yi < glm::min(y3, y4) - COLLISION_ERROR || yi >glm::max(y3, y4) + COLLISION_ERROR) return false;

	angle = -1.f * angle;
	nextPos = glm::vec2(xi, yi - 1);
	return true;
}

bool RectangleShape::CheckIntersectLeft(float x1, float y1, float x2, float y2, float &angle, glm::vec2& nextPos)
{
	float x3 = m_center.x - m_size.x / 2.f,
		  y3 = m_center.y + m_size.y / 2.f,
		  x4 = m_center.x - m_size.x / 2.f,
		  y4 = m_center.y - m_size.y / 2.f;

	float d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
	if (d == 0) return false;

	float xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
	float yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

	if (xi < glm::min(x1, x2) - COLLISION_ERROR || xi >glm::max(x1, x2) + COLLISION_ERROR) return false;
	if (xi < glm::min(x3, x4) - COLLISION_ERROR || xi >glm::max(x3, x4) + COLLISION_ERROR) return false;

	if (yi < glm::min(y1, y2) - COLLISION_ERROR || yi >glm::max(y1, y2) + COLLISION_ERROR) return false;
	if (yi < glm::min(y3, y4) - COLLISION_ERROR || yi >glm::max(y3, y4) + COLLISION_ERROR) return false;

	angle = 180 - angle;
	nextPos = glm::vec2(xi - 1, yi);
	return true;
}
bool RectangleShape::CheckIntersectUp(float x1, float y1, float x2, float y2, float &angle, glm::vec2& nextPos)
{
	float x3 = m_center.x - m_size.x / 2.f,
		  y3 = m_center.y + m_size.y / 2.f,
		  x4 = m_center.x + m_size.x / 2.f,
		  y4 = m_center.y + m_size.y / 2.f;

	float d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
	if (d == 0) return false;

	float xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
	float yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

	if (xi < glm::min(x1, x2) - COLLISION_ERROR || xi >glm::max(x1, x2) + COLLISION_ERROR) return false;
	if (xi < glm::min(x3, x4) - COLLISION_ERROR || xi >glm::max(x3, x4) + COLLISION_ERROR) return false;

	if (yi < glm::min(y1, y2) - COLLISION_ERROR || yi >glm::max(y1, y2) + COLLISION_ERROR) return false;
	if (yi < glm::min(y3, y4) - COLLISION_ERROR || yi >glm::max(y3, y4) + COLLISION_ERROR) return false;

	angle = -1.f * angle;
	nextPos = glm::vec2(xi, yi + 1);
	return true;
}
bool RectangleShape::CheckIntersectRight(float x1, float y1, float x2, float y2, float &angle, glm::vec2& nextPos)
{
	float x3 = m_center.x + m_size.x / 2.f,
		  y3 = m_center.y + m_size.y / 2.f,
		  x4 = m_center.x + m_size.x / 2.f,
		  y4 = m_center.y - m_size.y / 2.f;

	float d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
	if (d == 0) return false;

	float xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
	float yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

	if (xi < glm::min(x1, x2) - COLLISION_ERROR || xi >glm::max(x1, x2) + COLLISION_ERROR) return false;
	if (xi < glm::min(x3, x4) - COLLISION_ERROR || xi >glm::max(x3, x4) + COLLISION_ERROR) return false;

	if (yi < glm::min(y1, y2) - COLLISION_ERROR || yi >glm::max(y1, y2) + COLLISION_ERROR) return false;
	if (yi < glm::min(y3, y4) - COLLISION_ERROR || yi >glm::max(y3, y4) + COLLISION_ERROR) return false;

	angle = 180 - angle;
	nextPos = glm::vec2(xi + 1, yi);
	return true;
}
