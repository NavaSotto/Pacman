#include "Ghost.h"
#include "PacMan.h"
#include "Controller.h"
#include "Board.h"


Ghost::Ghost(sf::Vector2f place) : DynamicObject(place)
{
	m_texture = ResourceManager::instance().getPicture("ghost");

	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });

}

//collide by double dispatch
void Ghost::collide(DynamicObject * other, Controller& control)
{
	other->collide(this, control);
}

//collide with a pacman
void Ghost::collide(PacMan* pac, Controller& control)
{
	pac->setLives(pac->getLives() - 1);
	if (dynamic_cast<PacMan*>(pac))
		if (pac->getLives() == 0)
			control.removeMe(pac); //if the lives of the  pacman is finished
	control.putNew();
}

void Ghost::collide(Ghost * other, Controller&)
{
}

//collide with the passives
void Ghost::collide(StaticObject* other, Controller& control, Board& board, sf::Vector2f oldPlace)
{
	if (crashObjects(other->getObject(), m_last_side)) //If theres a type 1 crash - that there's a common point between two objects.
	{
		if (dynamic_cast<Wall*>(other))//crash with the walls
		{
			if (m_lastPos != m_last_side) //saves what direction it came to the walls from.
				m_last_side = m_lastPos;
			m_lastPos = 4;//stay  
			m_object.move({ oldPlace.x, oldPlace.y });//move to the old place
			return;
		}

	}
	return;

}

void Ghost::makePosition(Board & board, Controller& control)
{
	//Goes on the ghosts to found out each ghost is
	int index = 0;
	for (unsigned int i = 0; i < control.getGhosts().size(); i++)
	{//Place the ghosts.
		if (dynamic_cast<Ghost*>(control.getGhosts()[i]))
		{
			index++;//each number of the ghost is
			if (control.getGhosts()[i] == (Ghost*)(this))
				PutInPlace(index, board, control);
		}
	}
}

void Ghost::PutInPlace(int place, Board& board, Controller& control)
{
	int index_beginning = 0
		, index_end = Board::num_rows - 1;
	int k, m, x;

	//If is the first or the last ghost.
	if (place == 1 || place == 4)
	{
		x = index_end;	//Save the end index.
		while (index_beginning != index_end)//the Diagonals is not end	
		{

			for (int i = index_beginning; i <= index_end; i++)//
			{
				k = i;
				switch (place)	//According to current ghost.
				{
				case 1:
					m = index_beginning; break;
				case 4:
					m = x; break;

				}

				while (k != index_beginning - 1)//go back to his place
				{

					sf::Vector2f v = { k*Board::cubicle_size.x,m*Board::cubicle_size.y + 50 };
					if (!board.ifInPArry(v) && !control.ifInAcArry(v))//is empty
					{
						m_object.setPosition(v);
						return;
					}
					switch (place)
					{
					case 1://the first ghost
					{
						k--;
						m++;
					}break;
					case 4://the last ghost
					{
						k--;
						m--;
					}break;
					}
				}
			}
			//go to the next place of the Diagonal heads
			index_beginning++;
			x--;
		}
	}
	else
	{
		index_end = Board::num_cols - 1;
		x = index_beginning;
		while (index_end != index_beginning - 1)//the Diagonals is not end	
		{
			for (int i = index_end; i > index_beginning - 1; i--)
			{
				k = i;
				switch (place)//Aaccording to current ghost.
				{
				case 3:
					m = index_end; break;
				case 2:
					m = x; break;

				}
				while (k != index_end + 1)
				{
					sf::Vector2f v = { k*Board::cubicle_size.x,m*Board::cubicle_size.y + 50 };
					if (!board.ifInPArry(v) && !control.ifInAcArry(v))//is empty
					{
						m_object.setPosition(v);
						return;
					}
					switch (place)	//Aaccording to current ghost.
					{
					case 3:
					{
						k++;
						m--;
					}break;
					case 2:
					{
						k++;
						m++;
					}break;
					}
				}
			}
			//go to the next place of the Secondary diagonal
			index_end--;
			x++;
		}
	}

}


