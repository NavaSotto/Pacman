#include "SmartGhost.h"
#include "Controller.h"

SmartGhost::SmartGhost(int color, sf::Vector2f place) : Ghost(place)
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

//returns a moving value according to the pacmans location
int SmartGhost::moving(Controller& control)
{
	//an int is used in order to emphasise the little differences between him to the user pacman 
	if ((int)(m_object.getPosition().y) > (int)(control.getPacman()->getObject().getPosition().y))
		return 0;//up
	if ((int)(m_object.getPosition().y) < (int)(control.getPacman()->getObject().getPosition().y))
		return 1;//down
	if ((int)(m_object.getPosition().x) > (int)(control.getPacman()->getObject().getPosition().x))
		return 2;//left
	if ((int)(m_object.getPosition().x) < (int)(control.getPacman()->getObject().getPosition().x))
		return 3;//right
	return 4;
}

