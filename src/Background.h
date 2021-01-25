#pragma once
#ifndef _BACKGROUND_
#define _BACKGROUND_
#include "DisplayObject.h"
#include "TextureManager.h"

class Background : public DisplayObject
{
public:
	// constructor(s)
	Background();

	// destructor
	~Background();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	//getters and setters
	void setDestination(glm::vec2 destination);

private:

	glm::vec2 m_destination;

};

#endif /* defined (__Background__) */
