#include "PacMan.h"
#include "Controller.h"

const int LIVES = 3;

PacMan::PacMan(int color, sf::Vector2f place) : DynamicObject(place)
{
	m_texture = ResourceManager::instance().getPicture("pacman");
	m_object.setTexture(m_texture);
	switch (color)
	{
	case 0:
		m_object.setColor(sf::Color::Red);//'@'
		break;
	case 1:
		m_object.setColor(sf::Color::Green);//'W'
		break;
	case 2:
		m_object.setColor(sf::Color::Yellow);//S-BLUE
		break;
	case 3:
		m_object.setColor(sf::Color::Red);//'@'
		break;
	default:
		break;
	}
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });

	m_score = 0;
	m_lives = LIVES;

	if (m_sound.loadFromFile("EatSound.wav"))
		m_eatSound.setBuffer(m_sound);
}


int PacMan::getLives() const
{
	return m_lives;
}

void PacMan::setLives(int l)
{
	m_lives = l;
}

//collide by double dispatch
void PacMan::collide(DynamicObject * other, Controller& control)
{
	other->collide(this, control);
}

void PacMan::collide(PacMan * other, Controller&)
{
}

//collide with a ghost
void PacMan::collide(Ghost * ghost, Controller& control)
{
	setLives(getLives() - 1);
	if (dynamic_cast<PacMan*>(this))
		if (m_lives == 0)
			control.removeMe(this);
	control.putNew();//put new
}

//coliide with passive objects
void PacMan::collide(StaticObject* other, Controller& control, Board& board, sf::Vector2f oldPlace)
{
	if (crashObjects(other->getObject(), m_last_side)) //If theres a type 1 crash - that there's a common point between two objects.
	{
		if (dynamic_cast<Wall*>(other))
		{
			if (m_lastPos != 4)  //saves from what side it crashed into the walls
				m_last_side = m_lastPos;
			m_lastPos = 4;
			m_object.move({ oldPlace.x, oldPlace.y }); //returns to the last position
			return;//not remove the walls
		}

	}

	if (crashObjectsBorder(other->getObject(), m_last_side)) //if crashed into a cookie
	{
		if (dynamic_cast<HealthCookie*>(other))
		{
			control.reset_counter_time_health();
			cookieCrash(HealthCookie::m_SpeedIncrease, control); //increases speed accordingly
			board.removeMe(other);//deletes the cookie
			return;
		}
		if (dynamic_cast<PoisonCookie*>(other))
		{
			control.resetm_counter_time_poison();
			cookieCrash(PoisonCookie::m_speedIncreased, control); //decreases the speed accordingly
			board.removeMe(other);//deletes the cookie
			return;
		}
		if (dynamic_cast<Cookies*>(other))
		{
			cookieCrash(Cookies::m_speedIncrease, control);
			board.removeMe(other);//remove the cookie from the vector of the passives
			return;
		}
	}
	return;
}

void PacMan::makePosition(Board & board, Controller& control)
{
	int begin_row, end_row, begin_col, end_col;

	begin_row = end_row = Board::num_rows / 2;
	begin_col = end_col = Board::num_cols / 2;

	while (begin_row != -1 || end_row != Board::num_rows || begin_col != -1 || end_col != Board::num_cols)
	{
		for (int i = begin_row; i < end_row; i++)
		{
			for (int j = begin_col; j < end_col; i++)
			{
				sf::Vector2f v = { j*Board::cubicle_size.x,i*Board::cubicle_size.y + 50 };
				if (!board.ifInPArry(v) && !control.ifInAcArry(v))//is empty
				{
					m_object.setPosition(v);
					return;
				}
			}
		}
		if (begin_row > -1)
			begin_row--;
		if (begin_col > -1)
			begin_col--;
		if (end_row < Board::num_rows)
			end_row++;
		if (end_row < Board::num_cols)
			end_col++;
	}
}


int PacMan::getScore() const
{
	return m_score;
}

void PacMan::setScore(int score)
{
	m_score = score;
}

int PacMan::moving(Controller&)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_lastPos = 4;
		return 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_lastPos = 0;
		return 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_lastPos = 1;
		return 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_lastPos = 2;
		return 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_lastPos = 3;
		return 3;
	}
	return (m_lastPos);
}

void PacMan::cookieCrash(float value, Controller& control)
{
	m_speed *= value;
	m_score += (2 * (Controller::m_numLevel + 1));
	m_eatSound.play();

}

void PacMan::setSpeed(float newSpeed)
{
	m_speed = newSpeed;
}

