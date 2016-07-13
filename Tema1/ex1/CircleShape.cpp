#include "CircleShape.h"
#include "../dependente/glm/gtx/vector_angle.hpp"
#define PI 3.14159265359

CircleShape::CircleShape()
{
}

CircleShape::CircleShape(glm::vec2 center, float radius, glm::vec3 color, lab::BlackBox* blackBox) :
Shape(center, color, blackBox),
m_radius(radius)
{
	LoadMesh();
}

CircleShape::~CircleShape()
{
}

void CircleShape::LoadMesh()
{
	std::vector<MyVertexFormat> vertecsi;
	std::vector<glm::uvec3> indecsi;

	float interval = (360.f / 30.f) * PI / 180.f;

	vertecsi.push_back(MyVertexFormat(m_center.x, m_center.y));

	for (int i = 0; i < 30; ++i)
	{
		vertecsi.push_back(MyVertexFormat(m_center.x + m_radius * cos(i * interval), m_center.y + m_radius * sin(i * interval)));
	}

	for (int i = 1; i < 30; ++i)
	{
		indecsi.push_back(glm::uvec3(0, i, i + 1));
	}
	indecsi.push_back(glm::uvec3(0, 30, 1));

	//creaza vao
	unsigned int mesh_vao;
	glGenVertexArrays(1, &mesh_vao);
	glBindVertexArray(mesh_vao);

	//creeaza vbo
	unsigned int mesh_vbo;
	glGenBuffers(1, &mesh_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*vertecsi.size(), &vertecsi[0], GL_STATIC_DRAW);

	//creeaza ibo
	unsigned int mesh_ibo;
	glGenBuffers(1, &mesh_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indecsi.size() * 3, &indecsi[0], GL_STATIC_DRAW);

	//creez obiect de tip mesh
	m_mesh = new lab::Mesh(mesh_vbo, mesh_ibo, mesh_vao, indecsi.size() * 3);

	// traducem la OpenGL cum sa foloseasca datele noastre
	m_blackBox->bindMesh(m_mesh, sizeof(MyVertexFormat));

	m_mesh->setColor(m_color.x, m_color.y, m_color.z);
}

float CircleShape::GetRadius()
{
	return m_radius;
}

bool CircleShape::CheckIntersect(glm::vec2 point1, glm::vec2 point2, float &angle, glm::vec3& color, glm::vec2& nextPos)
{
	glm::vec2 d = point2 - point1, f = point1 - m_center;

	float	a = glm::dot(d, d),
			b = 2 * glm::dot(f, d),
			c = glm::dot(f, f) - m_radius * m_radius;

	float delta = b * b - 4 * a * c;

	bool collides = false;

	if (delta >= 0.f)
	{
		delta = glm::sqrt(delta);
		
		float t = (-b - delta) / (2 * a);

		if (t >= 0 && t <= 1)
		{
			collides = true;

			color = (color + m_color) / 2.f;

			glm::vec2 intersection = point1 + t * d;
			glm::vec2 normal = glm::normalize(intersection - m_center);
			glm::vec2 inverseIncident = glm::normalize(point1 - point2);
			glm::vec2 zeroDegree = glm::vec2(1.f, 0.f);

			if (angle < 0) angle = 360 + angle;

			float inversceIncidentAngle = glm::orientedAngle(zeroDegree, inverseIncident);
			float normalAngle = glm::orientedAngle(zeroDegree, normal);

			float deltaAngle = glm::abs(inversceIncidentAngle - normalAngle);
			

			if (inversceIncidentAngle > normalAngle)
			{
				angle = normalAngle - deltaAngle;
			}
			else
			{
				angle = normalAngle + deltaAngle;
			}

			nextPos = intersection + normal;

		}
	}

	

	return collides;
}
