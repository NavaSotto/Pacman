#include "DynamicObject.h"
#include "Controller.h"

float DynamicObject::speed = 250.f;

DynamicObject::DynamicObject(sf::Vector2f place) : Object(place)
{
	m_speed = speed;
}

void DynamicObject::setPosition(sf::Vector2f new_place)
{
	m_object.setPosition(new_place);
}

float DynamicObject::getSpeed() const
{
	return m_speed;
}

int DynamicObject::getLastPos() const
{
	return m_lastPos;
}

int DynamicObject::getLastSide() const
{
	return m_last_side;
}

void DynamicObject::move(float deltaTime, Controller& control, Board& board)
{
	sf::Vector2f oldPlace; //Saves the last position so if crashed with an walls will know where to go back to
	int caseNum = moving(control);//return from 0 to 3 where to move, then will move by polimorphism
	switch (caseNum)
	{
	case 0: {  //up
		if (m_object.getPosition().y - m_speed * deltaTime - 50 < 0)  //If the next step will be out of the board
		{
			m_object.move({ 0.f,Board::window_size.y - m_speed * deltaTime - 50 });
			oldPlace = { 0.f,m_speed*deltaTime - Board::window_size.y + 50 };
		}
		else
		{
			m_object.move(0.f, -m_speed * deltaTime);//go up
			oldPlace = { 0.f,m_speed*deltaTime };
		}
	}break;

	case 1: {//down
		if (m_object.getPosition().y + m_speed * deltaTime>Board::window_size.y)
		{
			m_object.move({ 0.f,-Board::window_size.y + m_speed * deltaTime + 50 });
			oldPlace = { 0.f,Board::window_size.y - m_speed * deltaTime - 50 };
		}
		else
		{
			m_object.move(0.f, m_speed*deltaTime);//go down
			oldPlace = { 0.f,-m_speed * deltaTime };
		}
	}break;

	case 2: {	//left
		if (m_object.getPosition().x - m_speed * deltaTime < 0)
		{
			m_object.move({ Board::window_size.x - m_speed * deltaTime,0.f });
			oldPlace = { -Board::window_size.x + m_speed * deltaTime,0.f };
		}
		else
		{
			m_object.move(-m_speed * deltaTime, 0.f);//go left
			oldPlace = { m_speed*deltaTime, 0.f };
		}
	}break;

	case 3: {//right
		if (m_object.getPosition().x + m_speed * deltaTime > Board::window_size.x)
		{
			m_object.move({ -Board::window_size.x + m_speed * deltaTime,0.f });
			oldPlace = { Board::window_size.x - m_speed * deltaTime,0.f };
		}
		else
		{
			m_object.move(m_speed*deltaTime, 0.f);//go right
			oldPlace = { -m_speed * deltaTime, 0.f };
		}
	}break;
	case 4:break;  //If crashed into an walls, stay there.
	}

	//Checks on the specific active object if crashed into any passive.
	for (unsigned int t = 0; t < board.getP().size(); t++)
		collide(board.getP()[t], control, board, oldPlace);

}




