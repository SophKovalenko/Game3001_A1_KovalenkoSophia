#include "Background.h"
#include "Util.h"

Background::Background()
{
	TextureManager::Instance()->load("../Assets/textures/bachground.png", "background");

	auto size = TextureManager::Instance()->getTextureSize("background");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	setType(BACKGROUND);
}

Background::~Background()
= default;

void Background::draw()
{
	TextureManager::Instance()->draw("background",
		getTransform()->position.x, getTransform()->position.y, 255, true);
}

void Background::update()
{
	
}

void Background::clean()
{
}

void Background::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}
