#pragma once

#include "../lab_blackbox.hpp"
#define COLLISION_ERROR 0.01f

class Shape
{
protected:

	lab::Mesh*		m_mesh;
	glm::vec2		m_center;
	glm::vec3		m_color;

	lab::BlackBox*	m_blackBox;


public:

	Shape();
	Shape(glm::vec2 center, glm::vec3 color, lab::BlackBox* blackBox);
	~Shape();

	virtual void	Draw();

	glm::vec2		GetCenter();
	glm::vec3		GetColor();
	virtual bool	CheckIntersect(glm::vec2 point1, glm::vec2 point2, float &angle, glm::vec3& color, glm::vec2& nextPos);

};


struct MyVertexFormat{
	glm::vec2 pozitie;
	MyVertexFormat(){
		pozitie = glm::vec2(0, 0);
	}
	MyVertexFormat(float px, float py){
		pozitie = glm::vec2(px, py);
	}
	MyVertexFormat operator=(const MyVertexFormat &rhs){
		pozitie = rhs.pozitie;
		return (*this);
	}
};
