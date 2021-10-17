#include "Wall.h"
#include "Board.h"

Wall::Wall(char c, sf::Vector2f place) :StaticObject(place)
{
	switch (c)
	{
	case '#':
		m_texture = ResourceManager::instance().getPicture("redWall");
		break;
	case 'E':
		m_texture = ResourceManager::instance().getPicture("greenWall");
		break;
	case 'D':
		m_texture = ResourceManager::instance().getPicture("blueWall");
		break;
	}
	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
}

Wall::~Wall()
{
}
