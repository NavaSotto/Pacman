#include "Controller.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include "SmartGhost.h"
#include "RandomGhost.h"
#include "Cookies.h"


const sf::Vector2f SIZE_BUTTON(170.f, 170.f);
const int NUM_LEVELS = 4;
int Controller::m_numLevel = 0;

Controller::Controller()
{
	m_pacman = new PacMan(m_numLevel);
	srand((unsigned int)time(NULL));
	if (m_music.openFromFile("music.wav"))
	{
		m_music.setVolume(20.f);
		m_music.play();
		m_music.setLoop(true);
	}

}

Controller::~Controller()
{
	for (unsigned int i = 0; i < m_ghosts.size(); i++)
	{
		delete m_ghosts[i];
	}
}

//manages the game structure
void Controller::manageGame()
{
	if (begin())//create a begining screen-call to: toPlay
		toPlay();
	else
		end();

}

//manages the levels in each game
void Controller::toPlay()
{
	do
	{
		initilize();//craete ghosts and pacmans
		putNew();
		if (play()) //if its time to go to next level
		{
			m_board.initilize();
			m_pacman->setScore(m_pacman->getScore() + (m_numLevel + 1) * 50);
		}
		else
			break;
	} while (m_numLevel <= NUM_LEVELS);

	end();

}

//initializes the players
void Controller::initilize()
{
	m_timer.restart();
	m_numLevel++;//updates the level number
	for (unsigned int i = 1; i < m_ghosts.size(); i++) //fress the old allocations
		delete m_ghosts[i];
	m_ghosts.clear();
	m_ghosts.push_back(m_pacman);

	int option;
	for (int i = 0; i < Controller::m_numLevel; i++)//adds ghosts according to level 
	{
		option = random(2);
		switch (option)//add a ghost
		{
		case 0:m_ghosts.push_back(new SmartGhost(m_numLevel));
			break;
		case 1:m_ghosts.push_back(new RandomGhost(m_numLevel));
			break;
		}
	}

}

//locates all the active objects
void Controller::putNew()
{
	for (unsigned int i = 0; i < m_ghosts.size(); i++)
		m_ghosts[i]->makePosition(m_board, (*this));//polimorphism that each one put himself in a good place
}

//begins the game
bool Controller::begin()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "PacMan");//Creating a window
	m_menu.createMenu(window.getSize().x, window.getSize().y);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				switch (m_menu.checkButton(event))
				{
				case 1:
					return true;
					break;
				case 2:
					return false;
					break;
				default:
					break;
				}
			}
			window.clear();
			m_menu.drawMenu(window);
			window.display();
		}
	}
}

//Plays the game
bool Controller::play()
{
	while (Cookies::total != 0 && getPacman()->getLives() != 0) //while you're still in the stage 
	{
		m_board.draw(m_ghosts, (*this));

		for (unsigned int i = 0; i < m_ghosts.size(); i++)  //moves and checks collide for each active object
		{
			float delta_time = (float)m_timer.restart().asSeconds(); //clock timer
			m_ghosts[i]->move(delta_time, (*this), m_board);

			m_board.draw(m_ghosts, (*this));

			for (unsigned int k = 0; k < m_ghosts.size(); k++)  //checks collide with all the other objects
				if (m_ghosts[i]->crashObjects(m_ghosts[k]->getObject(), m_ghosts[i]->getLastSide()))
					m_ghosts[i]->collide(m_ghosts[k], (*this));

			m_board.draw(m_ghosts, (*this));

			if (m_counter_time_health.getElapsedTime().asSeconds() >= 7)//set the new speed for 7 second if ate a poison cookie
				m_ghosts[i]->setSpeed(DynamicObject::speed);

			if (m_counter_time_poison.getElapsedTime().asSeconds() >= 14) //set the new speed for 14 second if ate an health cookie
				m_ghosts[i]->setSpeed(DynamicObject::speed);

			checkExit();
		}

	}
	if (getPacman()->getLives() == 0) //if the pacmans live are finished the game is over
	{
		return false;
	}
	return true;//the level is ended
}


//ends the game and starts a new one
void Controller::end()
{
	m_board.resetFile(); //closes & re-opens the file
	m_pacman = new PacMan(m_numLevel);
	m_numLevel = 0;
	m_board.initilize();

	ResourceManager::instance().getPicture("gameOver");
	m_background.setSmooth(true);
	sf::Sprite background;
	background.setTexture(m_background);
	background.scale(Board::window_size.x / background.getGlobalBounds().width, Board::window_size.y / background.getGlobalBounds().height);

	m_board.getWindow().draw(background);
	m_board.getWindow().display();

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//waits for a press
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//if pressed to exit
		{
			return;
		}
	}
	toPlay(); //start the game again
}

//checks if the player pressed on the exit or resize button
void Controller::checkExit()
{
	if (m_board.getWindow().isOpen())
	{
		for (sf::Event event; m_board.getWindow().pollEvent(event);)
		{
			switch (event.type) //depends what user requested
			{
			case sf::Event::Resized:	//screen size change
			{
				sf::View newView(sf::Vector2f(m_board.getWindow().getSize()) / 2.f,
					sf::Vector2f(m_board.getWindow().getSize()));
				m_board.getWindow().setView(newView);
				break;
			}
			case sf::Event::Closed:
				exit(0);
			}
		}
	}
}

PacMan* Controller::getPacman() const
{
	return m_pacman;//the user pacman 
}

std::vector<DynamicObject*> Controller::getGhosts() const
{
	return m_ghosts;
}

//receives a location and checks if theres an object with this location
bool Controller::ifInAcArry(sf::Vector2f place) const
{
	for (unsigned int i = 0; i < m_ghosts.size(); i++)
		if (place == m_ghosts[i]->getObject().getPosition())
			return true;
	return false;
}

//Removes a given active object from the vector
void Controller::removeMe(DynamicObject * active)
{
	for (unsigned int i = 0; i < m_ghosts.size(); i++)
		if (m_ghosts[i] == active)
		{
			removeCell(i);
			return;
		}
}

//removes a given cell number
void Controller::removeCell(int whereto)
{
	delete m_ghosts[whereto];
	m_ghosts.erase(m_ghosts.begin() + whereto);
}

void Controller::resetm_counter_time_poison()
{
	m_counter_time_poison.restart();
}

void Controller::reset_counter_time_health()
{
	m_counter_time_health.restart();
}

//-------A function which picks a random number between 0 and the limit.
int random(int limit)
{
	int v = rand() % limit;
	return (v);
}