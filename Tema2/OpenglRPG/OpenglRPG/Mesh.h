#pragma once

#include "Defines.h"
#include "VertexFormat.h"
#include <vector>
#include <string>

class Mesh
{
public:
	Mesh();
	Mesh(uint vbo, uint ibo, uint vao);
	~Mesh();

	void			SetColor(Vec3 color);
	void			LoadFromVectors(std::vector<VertexFormat> &vertices, std::vector<uint> &indices);
	void			LoadFromFile(const std::string& filename);
	void			Draw();

private:

	uint			m_vbo;
	uint			m_ibo;
	uint			m_vao;
	int				m_count;

	Vec3			m_color;
};

