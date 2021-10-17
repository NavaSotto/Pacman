#include "PoisonCookie.h"
#include "Board.h"

float PoisonCookie::m_speedIncreased = (float)0.9;

PoisonCookie::PoisonCookie(char c, sf::Vector2f place) : Cookies(c, place)
{
	createColor(c);
	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
}

PoisonCookie::~PoisonCookie()
{
}


void PoisonCookie::createColor(char c)
{
	switch (c)
	{
	case '*':
		m_texture = ResourceManager::instance().getPicture("poisonedRedCookie");
		break;
	case 'I':
		m_texture = ResourceManager::instance().getPicture("poisonedGreenCookie");
		break;
	case 'K':
		m_texture = ResourceManager::instance().getPicture("poisonedGreenCookie");
		m_object.setColor(sf::Color::Blue);
		break;
	}
}