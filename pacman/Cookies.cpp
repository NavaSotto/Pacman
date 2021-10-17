#include "Cookies.h"
#include "Board.h"

int Cookies::total = 0;  //counts how many cookies are there
float Cookies::m_speedIncrease = 1;

Cookies::Cookies(char c, sf::Vector2f place) : StaticObject(place)
{
	createColor(c);
	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
	total++;
}

Cookies::~Cookies()
{
	total--;
}

void Cookies::createColor(char c)
{
	switch (c)
	{
	case '*':
		m_texture = ResourceManager::instance().getPicture("standardRedCookie");
		break;
	case 'I':
		m_texture = ResourceManager::instance().getPicture("standardGreenCookie");
		break;
	case 'K':
		m_texture = ResourceManager::instance().getPicture("standardBlueCookie");
		break;
	}
}
