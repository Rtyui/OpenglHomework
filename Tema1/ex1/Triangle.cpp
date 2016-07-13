#include "Triangle.h"


Triangle::Triangle()
{
}


Triangle::Triangle(glm::vec2 center, glm::vec2 size, glm::vec3 color, lab::BlackBox* blackBox) :
Shape(center, color, blackBox),
m_size(size)
{
	LoadMesh();
}



Triangle::~Triangle()
{
}

void Triangle::LoadMesh()
{
	std::vector<MyVertexFormat> vertecsi;
	std::vector<glm::uvec3> indecsi;

	vertecsi.push_back(MyVertexFormat(m_center.x, m_center.y));
	vertecsi.push_back(MyVertexFormat(m_center.x + m_size.x, m_center.y));
	vertecsi.push_back(MyVertexFormat(m_center.x, m_center.y + m_size.y));

	indecsi.push_back(glm::uvec3(0, 1, 2));

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

bool Triangle::CheckIntersect(glm::vec2 point1, glm::vec2 point2, float &angle, glm::vec3& color, glm::vec2& nextPos)
{
	float x1 = point1.x, y1 = point1.y, x2 = point2.x, y2 = point2.y; //line 1
	float x3 = m_center.x + m_size.x,
		  y3 = m_center.y,
		  x4 = m_center.x,
		  y4 = m_center.y + m_size.y;

	float d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
	if (d == 0) return false;

	float xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
	float yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

	if (xi < glm::min(x1, x2) - COLLISION_ERROR || xi >glm::max(x1, x2) + COLLISION_ERROR) return false;
	if (xi < glm::min(x3, x4) - COLLISION_ERROR || xi >glm::max(x3, x4) + COLLISION_ERROR) return false;

	if (yi < glm::min(y1, y2) - COLLISION_ERROR || yi >glm::max(y1, y2) + COLLISION_ERROR) return false;
	if (yi < glm::min(y3, y4) - COLLISION_ERROR || yi >glm::max(y3, y4) + COLLISION_ERROR) return false;

	return true;
}