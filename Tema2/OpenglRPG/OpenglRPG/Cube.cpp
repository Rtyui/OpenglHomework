#include "Cube.h"
#include "RNG.h"

Cube::Cube()
{
}

Cube::Cube(float side)
{
	m_side = side;
	m_colored = false;

	std::vector<VertexFormat> vertices;
	std::vector<uint> indices;

	CreateModelVectors(vertices, indices);
	m_mesh.LoadFromVectors(vertices, indices);

}

Cube::Cube(float side, Vec3 color)
{
	m_side = side;

	m_color = color;
	m_colored = true;

	std::vector<VertexFormat> vertices;
	std::vector<uint> indices;

	CreateModelVectors(vertices, indices);
	m_mesh.LoadFromVectors(vertices, indices);
}

Cube::~Cube()
{
}

void Cube::CreateModelVectors(std::vector<VertexFormat> &vertices, std::vector<uint> &indices)
{
	float halfSide = m_side / 2.f;

	//Up verices
	vertices.push_back(VertexFormat(Vec3(-halfSide, halfSide, -halfSide), m_colored ? m_color : Vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f))));
	vertices.push_back(VertexFormat(Vec3(-halfSide, halfSide, halfSide), m_colored ? m_color : Vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f))));
	vertices.push_back(VertexFormat(Vec3(halfSide, halfSide, halfSide), m_colored ? m_color : Vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f))));
	vertices.push_back(VertexFormat(Vec3(halfSide, halfSide, -halfSide), m_colored ? m_color : Vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f))));

	//Down Verties
	vertices.push_back(VertexFormat(Vec3(-halfSide, -halfSide, -halfSide), m_colored ? m_color : Vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f))));
	vertices.push_back(VertexFormat(Vec3(-halfSide, -halfSide, halfSide), m_colored ? m_color : Vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f))));
	vertices.push_back(VertexFormat(Vec3(halfSide, -halfSide, halfSide), m_colored ? m_color : Vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f))));
	vertices.push_back(VertexFormat(Vec3(halfSide, -halfSide, -halfSide), m_colored ? m_color : Vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f))));

	//Up Faces
	indices.push_back(0), indices.push_back(1), indices.push_back(2);
	indices.push_back(0), indices.push_back(2), indices.push_back(3);

	//Front Faces
	indices.push_back(0), indices.push_back(3), indices.push_back(4);
	indices.push_back(4), indices.push_back(3), indices.push_back(7);

	//Right Faces
	indices.push_back(7), indices.push_back(3), indices.push_back(2);
	indices.push_back(7), indices.push_back(2), indices.push_back(6);

	//Back Faces
	indices.push_back(6), indices.push_back(2), indices.push_back(1);
	indices.push_back(6), indices.push_back(1), indices.push_back(5);

	//Left Faces
	indices.push_back(4), indices.push_back(1), indices.push_back(0);
	indices.push_back(4), indices.push_back(5), indices.push_back(1);

	//Down Faces
	indices.push_back(7), indices.push_back(6), indices.push_back(4);
	indices.push_back(4), indices.push_back(6), indices.push_back(5);

}

void Cube::CheckCollision(Shape3D *shape)
{

}

float Cube::GetSide()
{
	return m_side;
}