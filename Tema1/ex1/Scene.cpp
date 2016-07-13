#include "Scene.h"
#include "../dependente/freeglut/glut.h"
#include <ctime>
#include "RNG.h"


Scene::Scene(lab::BlackBox *blackBox)
{
	m_blackBox = blackBox;
	m_borderWidth = 10;

	m_width = 1000;
	m_height = 600;

	m_rayAngle = 0.f;
	m_rayVelocity = 5;
	m_raySize = 5;
	
	//Background Creation
	m_background = new RectangleShape(glm::vec2(m_width / 2, m_height / 2), glm::vec2(m_width, m_height), glm::vec3(0.7f, 0.7f, 0.7f), m_blackBox);

	//Camera Creation
	m_camera = new Triangle(glm::vec2(m_width, m_height), glm::vec2(-100, -100), glm::vec3(0.f, 0.f, 0.f), m_blackBox);

	//Lightsource Creation
	m_light = new CircleShape(glm::vec2(300.f, 500.f), 50, glm::vec3(1.f, 1.f, 0.f), m_blackBox);

	//Selector creation
	m_selector = new RectangleShape(glm::vec2(350.f, 500.f), glm::vec2(100.f, m_raySize), m_light->GetColor(), m_blackBox);

	ShuffleShapes();


	m_currentColor = m_light->GetColor();
	
	m_justIntersected = false;
	m_maxReflections = 30;
	m_reflections = 0;
	m_started = false;
	m_speedup = 1;
	glDisable(GL_DEPTH_TEST);
	ShowHelp();
}


Scene::~Scene()
{
	delete m_background;
	delete m_light;

	for (int i = 0; i < m_shapes.size(); ++i)
	{
		delete m_shapes[i];
	}
}

unsigned Scene::GetWidth()
{
	return m_width;
}

unsigned Scene::GetHeight()
{
	return m_height;
}

glm::mat3 Scene::MyIdentity(){
	return glm::mat3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
		);
}
glm::mat3 Scene::MyTranslate(float tx, float ty){
	return glm::mat3(
		1, 0, 0,
		0, 1, 0,
		tx, ty, 1
		);
}
glm::mat3 Scene::MyRotate(float u){
	return glm::mat3(
		cos(u), sin(u), 0,
		-sin(u), cos(u), 0,
		0, 0, 1
		);
}
glm::mat3 Scene::MyScale(float sx, float sy){
	return glm::mat3(
		sx, 0, 0,
		0, sy, 0,
		0, 0, 1
		);
}

void Scene::Draw()
{
	glViewport(0, 0, m_width, m_height);

	m_blackBox->setModelMatrix(MyIdentity());
	m_background->Draw();

	if (!m_started)
	{
		m_blackBox->setModelMatrix(MyTranslate(300.f, 500.f) * MyRotate(glm::radians(m_rayAngle)) * MyTranslate(-300.f, -500.f));
		m_selector->Draw();
	}

	m_light->Draw();

	for (unsigned i = 0; i < m_ray.size(); ++i)
	{
		m_blackBox->setModelMatrix(MyTranslate(m_ray[i]->GetCenter().x, m_ray[i]->GetCenter().y) *
			MyRotate(glm::radians(m_rotations[i])) *
			MyTranslate(-m_ray[i]->GetCenter().x, -m_ray[i]->GetCenter().y));
		m_ray[i]->Draw();
	}

	m_blackBox->setModelMatrix(MyIdentity());

	for (unsigned i = 0; i < m_shapes.size(); ++i)
	{
		m_shapes[i]->Draw();
	}

	m_camera->Draw();
}

void Scene::Update()
{
	for (int i = 0; i < m_speedup; ++i)
	{
		if (m_reflections < m_maxReflections && m_started)
		{
			InsertRayParticle();
		}
	}
	
}

void Scene::InsertRayParticle()
{
	if (m_ray.size() == 0)
	{
		//The ray first particle
		glm::vec2 firstParticleCenter = glm::vec2(m_light->GetCenter().x + cos(glm::radians(m_rayAngle)) * ((CircleShape*)m_light)->GetRadius(),
			m_light->GetCenter().y + sin(glm::radians(m_rayAngle)) * ((CircleShape*)m_light)->GetRadius());

		m_ray.push_back(new RectangleShape(firstParticleCenter, glm::vec2(m_rayVelocity, m_raySize), m_currentColor, m_blackBox));
		m_rotations.push_back(m_rayAngle);
	}
	else
	{
		auto nextParticleCenter = glm::vec2(m_ray[m_ray.size() - 1]->GetCenter().x + cos(glm::radians(m_rayAngle)) * m_rayVelocity,
			m_ray[m_ray.size() - 1]->GetCenter().y + sin(glm::radians(m_rayAngle)) * m_rayVelocity);

		if (m_camera->CheckIntersect(m_ray[m_ray.size() - 1]->GetCenter(), nextParticleCenter, m_rayAngle, m_currentColor, nextParticleCenter))
		{
			m_reflections = m_maxReflections;
			std::cout << "Camera Reached!" << std::endl;
			return;
		}

		for (unsigned i = 0; i < m_shapes.size(); ++i)
		{
			if (m_shapes[i]->CheckIntersect(m_ray[m_ray.size() - 1]->GetCenter(), nextParticleCenter, m_rayAngle, m_currentColor, nextParticleCenter))
			{
				m_reflections++;

				if (m_reflections == m_maxReflections)
				{
					std::cout << "Maximum number of reflections reached!" << std::endl;
					return;
				}
			}
		}

		m_ray.push_back(new RectangleShape(nextParticleCenter, glm::vec2(m_rayVelocity, m_raySize), m_currentColor, m_blackBox));
		m_rotations.push_back(m_rayAngle);

	}
}

void Scene::RaiseAngle()
{
	m_rayAngle += 1;
	if (m_rayAngle >= 360.f)
	{
		m_rayAngle -= 360;
	}
}

void Scene::LowerAngle()
{
	m_rayAngle -= 1;
	if (m_rayAngle < 0)
	{
		m_rayAngle = 360 + m_rayAngle;
	}
}

void Scene::Start()
{
	m_started = true;
}

void Scene::SetSpeedUp(int speedup)
{
	m_speedup = speedup;
	std::cout << "SpeedUp set to " << speedup << std::endl;
}

void Scene::ClearRay()
{
	m_started = false;
	for (unsigned i = 0; i < m_ray.size(); ++i)
	{
		delete m_ray[i];
	}
	m_ray.clear();
	m_rotations.clear();
	m_reflections = 0;
	m_rayAngle = 0.f;
	m_currentColor = m_light->GetColor();
}

float Distance(glm::vec2 p1, glm::vec2 p2)
{
	return (glm::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

void Scene::ShuffleShapes()
{

	for (int i = 0; i < m_shapes.size(); ++i)
	{
		delete m_shapes[i];
	}
	m_shapes.clear();

	RNG::SetSeed((unsigned)time(NULL));

	int shapesNumber = RNG::Int(10, 15);

	for (int i = 0; i < shapesNumber; ++i)
	{
		if ((rand() % 2) == 0)
		{
			auto center = glm::vec2(RNG::Float(50.f, 950.f), RNG::Float(50.f, 550.f));
			while (Distance(center, m_light->GetCenter()) < 150)
			{
				center = glm::vec2(RNG::Float(50.f, 950.f), RNG::Float(50.f, 550.f));
			}
			m_shapes.push_back(new CircleShape(center, RNG::Float(50, 100), glm::vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f)), m_blackBox));
		}
		else
		{
			auto center = glm::vec2(RNG::Float(50.f, 950.f), RNG::Float(50.f, 550.f));
			while (Distance(center, m_light->GetCenter()) < 150)
			{
				center = glm::vec2(RNG::Float(50.f, 950.f), RNG::Float(50.f, 550.f));
			}
			m_shapes.push_back(new RectangleShape(center, glm::vec2(RNG::Float(50, 150), RNG::Float(50, 200)), glm::vec3(RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f), RNG::Float(0.f, 1.f)), m_blackBox));
		}
	}

	Shape *downBorder = new RectangleShape(glm::vec2(m_width / 2, m_borderWidth / 2), glm::vec2(m_width, m_borderWidth), glm::vec3(0.f, 0.f, 0.f), m_blackBox);
	Shape *leftBorder = new RectangleShape(glm::vec2(m_borderWidth / 2, m_height / 2), glm::vec2(m_borderWidth, m_height), glm::vec3(0.f, 0.f, 0.f), m_blackBox);
	Shape *upBorder = new RectangleShape(glm::vec2(m_width / 2, m_height - m_borderWidth / 2), glm::vec2(m_width, m_borderWidth), glm::vec3(0.f, 0.f, 0.f), m_blackBox);
	Shape *rightBorder = new RectangleShape(glm::vec2(m_width - m_borderWidth / 2, m_height / 2), glm::vec2(m_borderWidth, m_height), glm::vec3(0.f, 0.f, 0.f), m_blackBox);

	m_shapes.push_back(downBorder);
	m_shapes.push_back(leftBorder);
	m_shapes.push_back(upBorder);
	m_shapes.push_back(rightBorder);
}

void Scene::SetMaxReflectionsNumber(int reflections)
{
	m_maxReflections = reflections;
	std::cout << "New max reflections is: " << m_maxReflections << std::endl;
}

int Scene::GetMaxReflectionsNumber()
{
	return m_maxReflections;
}

void Scene::ShowHelp()
{
	std::cout << "Commands: " << std::endl;
	std::cout << "Press 'h' to reload objects in the scene" << std::endl;
	std::cout << "Press 'c' to refresh ray" << std::endl;
	std::cout << "Press 'r' to raise ray angle" << std::endl;
	std::cout << "Press 'l' to lower ray angle" << std::endl;
	std::cout << "Press 's' to start the ray" << std::endl;
	std::cout << "Press from '1' to '4' to set ray speed" << std::endl;
	std::cout << "Press 'm' or 'M' to lower and to raise max number of reflections" << std::endl;
}