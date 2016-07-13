#pragma once

#include "Mesh.h"
#include "VertexFormat.h"

#include <vector>

class Shape3D
{
public:
	Shape3D();
	Shape3D(std::vector<VertexFormat> &vertices, std::vector<uint> &indices);
	~Shape3D();

	virtual void			Draw();
	virtual void			CheckCollision(Shape3D *shape);
	virtual void			Update(float dtime);

protected:

	Mesh					m_mesh;
};

