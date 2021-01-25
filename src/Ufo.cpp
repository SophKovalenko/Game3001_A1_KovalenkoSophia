#include "Ufo.h"
#include "Util.h"

Ufo::Ufo()
{
	TextureManager::Instance()->load("../Assets/textures/ufo.png", "ufo");

	auto size = TextureManager::Instance()->getTextureSize("ufo");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(UFO);
	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
}

Ufo::~Ufo()
= default;

void Ufo::draw()
{
	TextureManager::Instance()->draw("ufo",
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 60.0f));
}

void Ufo::update()
{
	m_Move();
}

void Ufo::clean()
{
}

void Ufo::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void Ufo::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void Ufo::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void Ufo::setRotation(float angle)
{
	m_rotationAngle = angle;
}

void Ufo::m_Move()
{
	m_targetDirection = m_destination - getTransform()->position;
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}