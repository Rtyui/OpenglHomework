#include "Shape3D.h"
#include "ShadersProgramsManager.h"

Shape3D::Shape3D()
{
}

Shape3D::Shape3D(std::vector<VertexFormat> &vertices, std::vector<uint> &indices)
{
	m_mesh.LoadFromVectors(vertices, indices);
}

Shape3D::~Shape3D()
{
}

void Shape3D::Draw()
{
	m_mesh.Draw();
}

void Shape3D::CheckCollision(Shape3D *shape)
{

}

void Shape3D::Update(float dtime)
{
}