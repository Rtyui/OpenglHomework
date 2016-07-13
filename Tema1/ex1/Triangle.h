#pragma once

#include "Shape.h"

class Triangle : public Shape
{
private:

	glm::vec2 m_size;

public:

	Triangle();
	Triangle(glm::vec2 center, glm::vec2 size, glm::vec3 color, lab::BlackBox* blackBox);
	~Triangle();

	void	LoadMesh();
	bool	CheckIntersect(glm::vec2 point1, glm::vec2 point2, float &angle, glm::vec3& color, glm::vec2& nextPos) override;
};

