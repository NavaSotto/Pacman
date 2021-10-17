#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"
#include <fstream>

class Board
{
public:
	//constructor
	Board();
	//distructor
	~Board();

	//static values
	static sf::Vector2f cubicle_size;//the size of a cubicle 
	static sf::Vector2f window_size;//the size of the window
	static int num_rows;
	static int num_cols;

	void initilize();//build the board from the file text
	void resetFile();//reset the files in the end of the game

	void removeMe(StaticObject*);//remove the passive object from the vector
	void removeCell(int);//remove a specific cell in the vector

	void draw(std::vector<DynamicObject*>, Controller&);


	bool ifInPArry(sf::Vector2f) const;//return if the object with the givin position is in the vector 

	sf::RenderWindow& getWindow();//return the window
	std::vector<StaticObject*> getP() const;//return the passive's vector

private:
	sf::RenderWindow m_window;//the main window
	sf::Texture m_Background;
	std::vector<StaticObject*> m_pObjects;//the passive objects
	std::ifstream m_myfile;//Board.txt
};

