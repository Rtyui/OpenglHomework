#pragma once

#include "Shape3D.h"

class Cube : public Shape3D
{
public:

	Cube();
	Cube(float side);
	Cube(float side, Vec3 color);
	~Cube();

	void					CreateModelVectors(std::vector<VertexFormat> &vertices, std::vector<uint> &indices);
	virtual void			CheckCollision(Shape3D *shape) override;

	float					GetSide();

private:

	float					m_side;

	Vec3					m_color;
	bool					m_colored;
};

