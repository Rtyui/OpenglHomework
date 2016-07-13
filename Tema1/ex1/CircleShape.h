#pragma once

#include "Shape.h"

class CircleShape : public Shape
{
private:

	float	m_radius;

	void	LoadMesh();

public:

	CircleShape();
	CircleShape(glm::vec2 center, float radius, glm::vec3 color, lab::BlackBox* blackBox);
	~CircleShape();

	float	GetRadius();
	bool	CheckIntersect(glm::vec2 point1, glm::vec2 point2, float &angle, glm::vec3& color, glm::vec2& nextPos) override;
};

