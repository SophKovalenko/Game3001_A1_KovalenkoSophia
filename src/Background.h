#pragma once
#ifndef _BACKGROUND_
#define _BACKGROUND_
#include "DisplayObject.h"
#include "TextureManager.h"

class Background : public DisplayObject
{
private: 
		/*SDL_Rect m_src;
	   SDL_Rect m_dst;
	   */
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
	/*void SetRekts(const SDL_Rect s, const SDL_Rect d)
	{
		m_src = s;
		m_dst = d;
	}
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetDst() { return &m_dst; }
	*/

	void setDestination(glm::vec2 destination);

private:

	//glm::vec2 m_destination;

};

#endif /* defined (__Background__) */
