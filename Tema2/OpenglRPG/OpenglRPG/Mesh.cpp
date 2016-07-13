#include "Mesh.h"
#include "glew\glew.h"
#include "Helpers.h"
#include "ShadersProgramsManager.h"

#include <fstream>
#include <iostream>
#include <vector>

Mesh::Mesh()
{
}

Mesh::Mesh(uint vbo, uint ibo, uint vao)
{
	m_vbo = vbo;
	m_ibo = ibo;
	m_vao = vao;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void Mesh::SetColor(Vec3 color)
{
	m_color = color;
}

void Mesh::LoadFromVectors(std::vector<VertexFormat> &vertices, std::vector<uint> &indices)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(float) * 3));

	m_count = indices.size();
}

void Mesh::LoadFromFile(const std::string& filename)
{
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good()){
		std::cout << "Mesh Loader: Obj file: " << filename << " not found." << std::endl;
		std::terminate();
	}

	std::vector<VertexFormat> vertices;
	std::vector<uint> indices;

	std::string line;
	std::vector<std::string> tokens, facetokens;
	std::vector<glm::vec3> positions;
	positions.reserve(1000);
	std::vector<glm::vec3> normals;
	normals.reserve(1000);
	std::vector<glm::vec2> texcoords;
	texcoords.reserve(1000);

	while (std::getline(file, line))
	{
		StringTokenize(line, tokens);

		if (tokens.size() == 0) continue;
		if (tokens.size()>0 && tokens[0].at(0) == '#') continue;
		if (tokens.size()>3 && tokens[0] == "v") positions.push_back(glm::vec3(StringToFloat(tokens[1]), StringToFloat(tokens[2]), StringToFloat(tokens[3])));
		if (tokens.size()>3 && tokens[0] == "vn") normals.push_back(glm::vec3(StringToFloat(tokens[1]), StringToFloat(tokens[2]), StringToFloat(tokens[3])));
		if (tokens.size()>2 && tokens[0] == "vt") texcoords.push_back(glm::vec2(StringToFloat(tokens[1]), StringToFloat(tokens[2])));
		if (tokens.size() >= 4 && tokens[0] == "f")
		{
			uint face_format = 0;

			if (tokens[1].find("//") != std::string::npos)
			{
				face_format = 3;
			}

			FaceTokenize(tokens[1], facetokens);

			if (facetokens.size() == 3) face_format = 4;
			else{
				if (facetokens.size() == 2){
					if (face_format != 3) face_format = 2;
				}
				else{
					face_format = 1;
				}
			}

			uint index_of_first_vertex_of_face = -1;


			for (uint num_token = 1; num_token<tokens.size(); num_token++)
			{
				if (tokens[num_token].at(0) == '#') break;

				FaceTokenize(tokens[num_token], facetokens);
				if (face_format == 1){

					int p_index = StringToInt(facetokens[0]);
					if (p_index>0) p_index -= 1;
					else p_index = positions.size() + p_index;

					vertices.push_back(VertexFormat(positions[p_index]));
				}
				else if (face_format == 2){

					int p_index = StringToInt(facetokens[0]);
					if (p_index>0) p_index -= 1;
					else p_index = positions.size() + p_index;

					int t_index = StringToInt(facetokens[1]);
					if (t_index>0) t_index -= 1;
					else t_index = texcoords.size() + t_index;

					vertices.push_back(VertexFormat(positions[p_index], texcoords[t_index]));
				}
				else if (face_format == 3){

					int p_index = StringToInt(facetokens[0]);
					if (p_index>0) p_index -= 1;
					else p_index = positions.size() + p_index;

					int n_index = StringToInt(facetokens[1]);
					if (n_index>0) n_index -= 1;
					else n_index = normals.size() + n_index;

					vertices.push_back(VertexFormat(positions[p_index], normals[n_index]));
				}
				else{

					int p_index = StringToInt(facetokens[0]);
					if (p_index>0) p_index -= 1;
					else p_index = positions.size() + p_index;

					int t_index = StringToInt(facetokens[1]);
					if (t_index>0) t_index -= 1;
					else t_index = normals.size() + t_index;

					int n_index = StringToInt(facetokens[2]);
					if (n_index>0) n_index -= 1;
					else n_index = normals.size() + n_index;

					vertices.push_back(VertexFormat(positions[p_index], normals[n_index], texcoords[t_index]));
				}

				if (num_token<4){
					if (num_token == 1) index_of_first_vertex_of_face = vertices.size() - 1;
					indices.push_back(vertices.size() - 1);
				}
				else{
					indices.push_back(index_of_first_vertex_of_face);
					indices.push_back(vertices.size() - 2);
					indices.push_back(vertices.size() - 1);
				}
			}
		}
	}

	LoadFromVectors(vertices, indices);

}

void Mesh::Draw()
{
	glUniform3f(g_shadersManager->GetUniformLocation(0, "in_color"), m_color.r, m_color.g, m_color.b);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, (void*)0);
}
