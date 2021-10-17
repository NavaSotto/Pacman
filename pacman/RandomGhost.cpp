#include "RandomGhost.h"
#include "Controller.h"

RandomGhost::RandomGhost(int color, sf::Vector2f place) : Ghost(place)
{
	switch (color)
	{
	case 0:
		m_object.setColor(sf::Color::Red);//'%'
		break;
	case 1:
		m_object.setColor(sf::Color::Green);//'T'
		break;
	case 2:
		m_object.setColor(sf::Color::Yellow);//'G'-BLUE
		break;
	case 3:
		m_object.setColor(sf::Color::Red);//'%'
		break;
	default:
		break;
	}
}

int RandomGhost::moving(Controller&)
{
	int x = random(25);
	if (x == 8)
		m_lastPos = (random(4));
	return m_lastPos;
}

