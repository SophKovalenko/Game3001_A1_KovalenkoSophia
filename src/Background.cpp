#include "Background.h"

Background::Background()
{
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");

	auto size = TextureManager::Instance()->getTextureSize("background");
	setWidth(800);
	setHeight(600);
	setEnabled(true);
	setType(BACKGROUND);
}

Background::~Background()
= default;

void Background::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("background", 300, 300, 0, 0, true, SDL_FLIP_NONE);
		//getTransform()->position.x, getTransform()->position.y, 255, true);
}

void Background::update()
{
	
}

void Background::clean()
{
}

void Background::setDestination(const glm::vec2 destination)
{
	//m_destination = destination;
}
