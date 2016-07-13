#include "Player.h"
#include "Cube.h"
#include "ShadersProgramsManager.h"
#include "Input.h"
#include "Platform.h"
#include "App.h"

#include <iostream>

Player::Player()
{
}

Player::Player(Vec3 position, Camera* tpc, Camera* fpc) :
Object(position)
{
	m_collider = new Cube(5);
	m_tpc = tpc;
	m_fpc = fpc;
	m_fpc->SetPosition(m_position);
	m_tpc->SetPosition(m_position + Vec3(0.f, 0.f, DISTANCE_TO_PLAYER));
	m_jumpVelocity = 0;
	m_gravityAccel = -5.f;
	m_jumping = false;
	m_ableToJump = false;
}

Player::~Player()
{
}

void Player::Update(float dtime)
{

	m_tpc->Update(dtime);
	m_fpc->Update(dtime);

	m_jumpVelocity += m_gravityAccel;

	if (g_input->IsKeyPressed("KeyA") && !m_tpc->IsRotating())
	{
		AddToPosition(-PLAYER_SPEED * m_tpc->GetRight() * dtime);
		m_fpc->SetForward(-1.f * m_tpc->GetRight());
		m_fpc->SetRight(m_fpc->GetForward());
	}
	if (g_input->IsKeyPressed("KeyD") && !m_tpc->IsRotating())
	{
		AddToPosition(PLAYER_SPEED * m_tpc->GetRight() * dtime);
		m_fpc->SetForward(m_tpc->GetRight());
		m_fpc->SetRight(-1.f * m_fpc->GetForward());
	}
	if (g_input->WasKeyJustPressed("KeySpace") && !m_tpc->IsRotating() && !m_jumping && m_ableToJump)
	{
		m_jumpVelocity = PLAYER_JUMP;
		m_jumping = true;
	}
	if (g_input->WasKeyJustPressed("KeyLeft") && !m_tpc->IsRotating() && !m_jumping)
	{
		m_tpc->RequireRotateY(90.f);
		m_fpc->RequireRotateY(90.f);
	}
	if (g_input->WasKeyJustPressed("KeyRight") && !m_tpc->IsRotating() && !m_jumping)
	{
		m_tpc->RequireRotateY(-90.f);
		m_fpc->RequireRotateY(-90.f);
	}

	AddToPosition(Vec3(0.f, m_jumpVelocity * dtime, 0.f));
	m_ableToJump = false;

}

void Player::Draw()
{
	Object::Draw();
}

void Player::CheckCollision(Object *object)
{

	auto collider = object->GetCollider();

	auto cubeCollider = dynamic_cast<Cube*>(collider);
	if (cubeCollider)
	{
		float halfSidesSum = cubeCollider->GetSide() / 2.f + ((Cube*)m_collider)->GetSide() / 2.f;
		Vec3 distanceVec = m_position - object->GetPosition();
		Vec3 absDistanceVec = glm::abs(distanceVec);

		if (absDistanceVec.x <= halfSidesSum && absDistanceVec.y <= halfSidesSum && absDistanceVec.z <= halfSidesSum)
		{
			if (((Platform*)object)->IsFinish())
			{
				std::cout << "Good Game! You Win." << std::endl;
				g_app->m_gameRunning = false;
			}

			float max = glm::max(glm::max(absDistanceVec.x, absDistanceVec.y), absDistanceVec.z);
			Vec3 delta = Vec3(	absDistanceVec.x == max ? halfSidesSum - absDistanceVec.x : 0.f,
								absDistanceVec.y == max ? halfSidesSum - absDistanceVec.y : 0.f,
								absDistanceVec.z == max ? halfSidesSum - absDistanceVec.z : 0.f);
			delta = delta * ((distanceVec + Vec3(1.f)) / (absDistanceVec + Vec3(1.f)));
			if (absDistanceVec.y == max)
			{
				m_ableToJump = true;
				m_jumping = false;
				m_jumpVelocity = 0;
			}
			AddToPosition(delta);
		}
	}
}

void Player::AddToPosition(Vec3 deltaPosition)
{
	Object::AddToPosition(deltaPosition);
	m_tpc->AddToPosition(deltaPosition);
	m_fpc->AddToPosition(deltaPosition);

}