#include "Ufo.h"
#include "Game.h"
#include "Util.h"

Ufo::Ufo()
{
	TextureManager::Instance()->load("../Assets/textures/ufo.png", "ufo");

	auto size = TextureManager::Instance()->getTextureSize("ufo");
	setWidth(size.x);
	setHeight(size.y);

	/*THIS IS NEW
    setPosition(glm::vec2(400.0f, 300.0f);
	setVelocity(glm::vec2(0.0f, 0.0f));
	setSteerState(IDLE);
	*/


	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(UFO);

	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
}

Ufo::~Ufo()
= default;

void Ufo::draw()
{
	TextureManager::Instance()->draw("ufo",
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(m_leftWhisker.Start(), m_leftWhisker.End());
	Util::DrawLine(m_rightWhisker.Start(), m_rightWhisker.End());
	Util::DrawLine(m_centerWhisker.Start(), m_centerWhisker.End());
}

void Ufo::update()
{
	m_leftWhisker.SetLine(getTransform()->position,
		(getTransform()->position + Util::getOrientation(m_rotationAngle - 40) * 100.0f));

	m_rightWhisker.SetLine(getTransform()->position,
		(getTransform()->position + Util::getOrientation(m_rotationAngle + 40) * 100.0f));

	m_centerWhisker.SetLine(getTransform()->position,
		(getTransform()->position + Util::getOrientation(m_rotationAngle) * 100.0f));

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

glm::vec2 Ufo::getOrientation() const
{
	return m_orientation;
}

void Ufo::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float Ufo::getTurnRate() const
{
	return m_turnRate;
}

void Ufo::setTurnRate(float rate)
{
	m_turnRate = rate;
}

float Ufo::getAccelerationRate() const
{
	return m_accelerationRate;
}

void Ufo::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void Ufo::setLeftWhisker(glm::vec2 start, glm::vec2 end)
{
	m_leftWhisker.SetLine(start, end);
}

void Ufo::setRightWhisker(glm::vec2 start, glm::vec2 end)
{
	m_rightWhisker.SetLine(start, end);
}

float Ufo::getRotation() const
{
	return m_rotationAngle;
}

void Ufo::setRotation(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	//convert the angle to a normalized vector and store it in orientation
	setOrientation(glm::vec2(x, y));
}

void Ufo::m_Move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}

	//std::cout << "Target Rotation: " << target_rotation << std::endl;

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	//using the formula pf = pi + vi + 0.5ai*t^2 
	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime); // scale our velocity

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity; 

	/*new stuff

	float angleToTarget = Util::signedAngle();

		if (angleToTarget > 0.0f)
		{
		
		}*/
}