#include "HealthCookie.h"
#include "Board.h"

float HealthCookie::m_SpeedIncrease = (float)1.2;

HealthCookie::HealthCookie(char c, sf::Vector2f place) :Cookies(c, place)
{
	createColor(c);
	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
}

HealthCookie::~HealthCookie()
{
}

void HealthCookie::createColor(char c)
{
	switch (c)
	{
	case '*':
		m_texture = ResourceManager::instance().getPicture("healthyRedCookie");
		break;
	case 'I':
		m_texture = ResourceManager::instance().getPicture("healthyGreenCookie");
		break;
	case 'K':
		m_texture = ResourceManager::instance().getPicture("healthyBlueCookie");
		break;
	}
}