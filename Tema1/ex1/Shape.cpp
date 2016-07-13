#include "Shape.h"


Shape::Shape()
{
}

Shape::Shape(glm::vec2 center, glm::vec3 color, lab::BlackBox* blackBox) :
m_center(center),
m_blackBox(blackBox),
m_color(color)
{
}


Shape::~Shape()
{
}

void Shape::Draw()
{
	m_blackBox->drawMesh(m_mesh, 1);
}

glm::vec2 Shape::GetCenter()
{
	return m_center;
}

glm::vec3 Shape::GetColor()
{
	return m_color;
}

bool Shape::CheckIntersect(glm::vec2 point1, glm::vec2 point2, float &angle, glm::vec3& color, glm::vec2& nextPos)
{
	return false;
}