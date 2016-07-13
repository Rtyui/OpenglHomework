#pragma once

#include "Shape.h"

class RectangleShape : public Shape
{
private:

	glm::vec2		m_size;

	void			LoadMesh();

	bool			CheckIntersectDown(float x1, float y1, float x2, float y2, float &angle, glm::vec2& nextPos);
	bool			CheckIntersectLeft(float x1, float y1, float x2, float y2, float &angle, glm::vec2& nextPos);
	bool			CheckIntersectUp(float x1, float y1, float x2, float y2, float &angle, glm::vec2& nextPos);
	bool			CheckIntersectRight(float x1, float y1, float x2, float y2, float &angle, glm::vec2& nextPos);

public:
	RectangleShape();
	RectangleShape(glm::vec2 center, glm::vec2 size, glm::vec3 color, lab::BlackBox* blackBox);
	~RectangleShape();

	bool			CheckIntersect(glm::vec2 point1, glm::vec2 point2, float &angle, glm::vec3& color, glm::vec2& nextPos) override;
};

