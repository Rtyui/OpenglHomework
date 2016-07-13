#pragma once

#include "../dependente/glm/glm.hpp"
#include "../lab_blackbox.hpp"
#include "CircleShape.h"
#include "RectangleShape.h"
#include "Triangle.h"

class Scene
{
private:

	lab::BlackBox*				m_blackBox;

	Shape*						m_background;
	Shape*						m_light;
	Shape*						m_camera;
	Shape*						m_selector;

	std::vector<Shape*>			m_shapes;

	unsigned					m_width;
	unsigned					m_height;

	unsigned					m_borderWidth;

	float						m_rayAngle;
	float						m_rayVelocity;
	float						m_raySize;

	std::vector<Shape*>			m_ray;
	std::vector<float>			m_rotations;

	glm::vec3					m_currentColor;

	bool						m_justIntersected;

	int							m_maxReflections;
	int							m_reflections;

	bool						m_started;

	int							m_speedup;

public:

	Scene(lab::BlackBox *blackBox);
	~Scene();

	unsigned	GetWidth();
	unsigned	GetHeight();
	
	glm::mat3	MyIdentity();
	glm::mat3	MyTranslate(float tx, float ty);
	glm::mat3	MyRotate(float u);
	glm::mat3	MyScale(float sx, float sy);

	void		Draw();
	void		Update();

	void		InsertRayParticle();
	void		RaiseAngle();
	void		LowerAngle();
	void		Start();
	void		SetSpeedUp(int speedup);
	void		ClearRay();
	void		ShuffleShapes();

	void		SetMaxReflectionsNumber(int number);
	int			GetMaxReflectionsNumber();

	void		ShowHelp();
};

