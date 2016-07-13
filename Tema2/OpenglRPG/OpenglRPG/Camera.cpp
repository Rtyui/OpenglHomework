#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"
#include "ShadersProgramsManager.h"
#include "App.h"


Camera::Camera()
{
	m_type = TPC;
	m_forward = Vec3(0.f, 0.f, -1.f);
	m_up = Vec3(0.f, 1.f, 0.f);
	m_right = Vec3(1.f, 0.f, 0.f);
	m_position = Vec3(0.f, 0.f, 100.f);
}

Camera::Camera(TYPE t)
{
	m_type = t;
	if (m_type == TPC)
	{
		m_forward = Vec3(0.f, 0.f, -1.f);
		m_up = Vec3(0.f, 1.f, 0.f);
		m_right = Vec3(1.f, 0.f, 0.f);
		m_position = Vec3(0.f, 0.f, DISTANCE_TO_PLAYER);
	}
	else if (m_type == FPC)
	{
		m_forward = Vec3(0.f, 0.f, -1.f);
		m_up = Vec3(0.f, 1.f, 0.f);
		m_right = Vec3(1.f, 0.f, 0.f);
		m_position = Vec3(0.f, 0.f, 0.f);
	}

	m_rotating = false;
	m_rotatingTime = 0.f;
	m_currentRotatingAngle = 0.f;
}

Camera::~Camera()
{
}

void Camera::Update(float dtime)
{
	if (m_rotating)
	{
		float diff = glm::min(m_rotatingTime, dtime);
		m_rotatingTime -= diff;

		RotateY(m_currentRotatingAngle * diff);

		if (m_rotatingTime == 0.f)
		{
			m_rotating = false;
		}
	}
}

void Camera::LoadMatrices()
{
	if (m_type == TPC)
	{
		auto viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
		g_shadersManager->SetViewMatrix(viewMatrix);

		auto projectionMatrix = glm::ortho(-ORTHO_SIZE, ORTHO_SIZE, -ORTHO_SIZE, ORTHO_SIZE, PROJ_NEAR, PROJ_FAR);
		g_shadersManager->SetProjectionMatrix(projectionMatrix);
	}
	else if (m_type == FPC)
	{
		auto viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
		g_shadersManager->SetViewMatrix(viewMatrix);

		auto projectionMatrix = glm::perspective(PERSPECTIVE_FOV, (float)g_app->m_windowWidth / g_app->m_windowHeight, PROJ_NEAR, PROJ_FAR);
		g_shadersManager->SetProjectionMatrix(projectionMatrix);
	}
}

void Camera::SetForward(Vec3 forward)
{
	m_forward = forward;
}

Vec3 Camera::GetForward()
{
	return m_forward;
}

void Camera::SetRight(Vec3 right)
{
	m_right = right;
}

Vec3 Camera::GetRight()
{
	return m_right;
}

void Camera::AddToPosition(Vec3 deltaPosition)
{
	m_position += deltaPosition;
}

void Camera::SetPosition(Vec3 position)
{
	m_position = position;
}

void Camera::RotateY(float angle)
{
	if (m_type == TPC)
	{
		m_position = Vec3(glm::translate(Mat4(1.f), m_forward * DISTANCE_TO_PLAYER) * Vec4(m_position, 1.f));
		m_forward = glm::normalize(glm::vec3(glm::rotate(Mat4(1.f), angle, m_up) * Vec4(m_forward, 1.f)));
		m_right = glm::normalize(glm::vec3(glm::rotate(Mat4(1.f), angle, m_up) * Vec4(m_right, 1.f)));
		m_position = Vec3(glm::translate(Mat4(1.f), m_forward * -DISTANCE_TO_PLAYER) * Vec4(m_position, 1.f));
	}
	else if (m_type == FPC)
	{
		m_forward = glm::normalize(glm::vec3(glm::rotate(Mat4(1.f), angle, m_up) * Vec4(m_forward, 1.f)));
		m_right = glm::normalize(glm::vec3(glm::rotate(Mat4(1.f), angle, m_up) * Vec4(m_right, 1.f)));
	}
}

void Camera::RequireRotateY(float angle)
{
	m_rotating = true;
	m_currentRotatingAngle = angle;
	m_rotatingTime = TIME_TO_ROTATE;
}

bool Camera::IsRotating()
{
	return m_rotating;
}

void Camera::SetViewport()
{
	if (m_type == TPC)
	{
		glEnable(GL_SCISSOR_TEST);
		glViewport(0, 0, g_app->m_windowWidth, g_app->m_windowHeight);
		glScissor(0, 0, g_app->m_windowWidth, g_app->m_windowHeight);
	}
	else if (m_type == FPC)
	{
		glEnable(GL_SCISSOR_TEST);
		glViewport(g_app->m_windowWidth * 0.7f, g_app->m_windowHeight * 0.7f, g_app->m_windowWidth * 0.3f, g_app->m_windowHeight * 0.3f);
		glScissor(g_app->m_windowWidth * 0.7f, g_app->m_windowHeight * 0.7f, g_app->m_windowWidth * 0.3f, g_app->m_windowHeight * 0.3f);
	}
}