#include "Object.h"
#include "glm\gtc\matrix_transform.hpp"
#include "ShadersProgramsManager.h"


Object::Object()
{
}

Object::Object(Vec3 position)
{
	m_position = position;
	m_model = glm::translate(Mat4(1.f), m_position);
}

Object::~Object()
{
	delete m_collider;
}

void Object::Draw()
{
	g_shadersManager->SetModelMatrix(m_model);
	m_collider->Draw();
	g_shadersManager->SetModelMatrix(IDENTITY4);
}

void Object::SetPosition(Vec3 position)
{
	m_model = glm::translate(m_model, position - m_position);
	m_position = position;
}

void Object::AddToPosition(Vec3 deltaPosition)
{
	m_model = glm::translate(m_model, deltaPosition);
	m_position = m_position + deltaPosition;
}

Vec3 Object::GetPosition()
{
	return m_position;
}

void Object::CheckCollision(Object *object)
{

}

void Object::Update(float dtime)
{
}

Shape3D* Object::GetCollider()
{
	return m_collider;
}
