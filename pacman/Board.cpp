#include "Board.h"
#include "Controller.h"
#include "wall.h"
#include "Cookies.h"
#include "HealthCookie.h"
#include "PoisonCookie.h"
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include<string>

sf::Vector2f Board::window_size;
sf::Vector2f Board::cubicle_size;
int Board::num_rows;
int Board::num_cols;

Board::Board()
{
	m_window.create(sf::VideoMode(700, 700), "Pacman");
	m_Background = ResourceManager::instance().getPicture("background");
	m_Background.setSmooth(true);

	m_myfile.open("Board.txt");
	initilize();  //creates the board from the text file
}

Board::~Board()
{
	m_myfile.close();
	for (unsigned int i = 0; i < m_pObjects.size(); i++)
	{
		delete m_pObjects[i];  //frees the dynamic allocations
	}
}

std::vector<StaticObject*> Board::getP() const
{
	return m_pObjects;
}

void Board::initilize()
{
	for (unsigned int i = 0; i < m_pObjects.size(); i++)
		delete m_pObjects[i];
	m_pObjects.clear();
	std::string line;
	if (m_myfile.is_open())
	{
		getline(m_myfile, line);	//Read a line.
		num_rows = atoi(line.c_str());//reads the number of rows

		getline(m_myfile, line);
		num_cols = atoi(line.c_str());  //reads the number of columns

		window_size = { (float)(m_window.getSize().x), (float)(m_window.getSize().y) };//saves the window's size  
		cubicle_size = { window_size.x / num_cols ,(window_size.y - 50) / num_rows };//calculates accordingly the cubicle size

		int picked = 0;  //will be picked randomly to decide what type 
		for (int i = 0; i < num_rows; i++)
		{
			for (int j = 0; j < num_cols; j++)
			{
				char c = m_myfile.get();
				switch (c)
				{
				case ('#'):  //if its an walls
				case ('E'):
				case ('D'):
				{
					m_pObjects.push_back(new Wall(c, { (cubicle_size.x)*j,(cubicle_size.y)*i + 50 }));
				}break;
				case ('*'):  //if its a cookie
				case ('I'):
				case ('K'):
				{
					picked = random(3);
					switch (picked)
					{
					case 0:
						m_pObjects.push_back(new Cookies(c, { (cubicle_size.x)*j,(cubicle_size.y)*i + 50 }));
						break;
					case 1:
						m_pObjects.push_back(new HealthCookie(c, { (cubicle_size.x)*j,(cubicle_size.y)*i + 50 }));
						break;
					case 2:
						m_pObjects.push_back(new PoisonCookie(c, { (cubicle_size.x)*j,(cubicle_size.y)*i + 50 }));
						break;
					}
				}break;
				}
			}
			m_myfile.get();
		}
	}
}

void Board::resetFile()   //when starts the game again we need to read the file from the beginning
{
	m_myfile.close();
	m_myfile.open("Board.txt");
}

//Will draw the board
void Board::draw(std::vector<DynamicObject*> Vplayers, Controller& control)
{
	m_window.clear(sf::Color::White);

	sf::Font font;
	font.loadFromFile("Toledo__.ttf"); //loading from an existing font

	sf::Sprite m_backgrounds;
	m_backgrounds.setTexture(m_Background);
	m_backgrounds.scale(Board::window_size.x / m_backgrounds.getGlobalBounds().width, Board::window_size.y / m_backgrounds.getGlobalBounds().height);

	m_backgrounds.setTexture(m_Background);
	m_window.draw(m_backgrounds);

	//setting the lives display
	sf::Text lives;
	lives.setPosition({ 30, 4 });
	lives.setFont(font);
	lives.setCharacterSize(28);
	//	lives.setColor(sf::Color::Black);
	lives.setString(static_cast<std::ostringstream*>(&(std::ostringstream() << control.getPacman()->getLives()))->str());
	m_window.draw(lives);

	//setting the score display
	sf::Text score;
	score.setPosition({ 190,4 });
	score.setFont(font);
	score.setCharacterSize(28);
	//	score.setColor(sf::Color::Black);
	score.setString(static_cast<std::ostringstream*>(&(std::ostringstream() << control.getPacman()->getScore()))->str());
	m_window.draw(score);

	for (unsigned int i = 0; i < m_pObjects.size(); i++)
		m_window.draw(m_pObjects[i]->getObject());

	for (unsigned int i = 0; i < Vplayers.size(); i++)
		m_window.draw(Vplayers[i]->getObject());

	m_window.display();

}



//Removes a given passive object from the vector
void Board::removeMe(StaticObject * passive)
{
	for (unsigned int i = 0; i < m_pObjects.size(); i++)
		if (m_pObjects[i] == passive)
		{
			removeCell(i);
			return;
		}
}

//removes a given cell number
void Board::removeCell(int whereto)
{
	delete m_pObjects[whereto];
	m_pObjects.erase(m_pObjects.begin() + whereto);
}

//receives a location and checks if theres an object with this location
bool Board::ifInPArry(sf::Vector2f place) const
{
	for (unsigned int i = 0; i < m_pObjects.size(); i++)
		if (place == m_pObjects[i]->getObject().getPosition())
			return true;
	return false;
}

sf::RenderWindow & Board::getWindow()
{
	return m_window;
}

