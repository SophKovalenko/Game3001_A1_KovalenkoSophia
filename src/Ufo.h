#pragma once
#ifndef __UFO__
#define __UFO__
#include "DisplayObject.h"
#include "TextureManager.h"

class Ufo final : public DisplayObject
{
public:
	// constructor(s)
	Ufo();

	// destructor
	~Ufo();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	//getters and setters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation() const;
	void setOrientation(const glm::vec2 orientation);
	float getRotation() const;
	void setRotation(const float angle);
	float getTurnRate() const;
	void setTurnRate(float rate);
	float getAccelerationRate() const;
	void setAccelerationRate(const float rate);

private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	void m_Move();

};

#endif /* defined (__UFO__) */
