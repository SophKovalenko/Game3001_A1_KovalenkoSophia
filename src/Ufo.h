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
	void setOrientation(glm::vec2 orientation);
	void setRotation(float angle);

private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;

	void m_Move();

};

#endif /* defined (__Ufo__) */
