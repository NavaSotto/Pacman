#pragma once
#include "DynamicObject.h"
#include "PacMan.h"
#include "Board.h"
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "ResourceManager.h"

class Controller
{


public:
	static int m_numLevel;//saves the current num of level

	Controller();
	~Controller();

	PacMan* getPacman() const;//return the user
	std::vector<DynamicObject*> getGhosts() const;//return the players' vector 
	bool ifInAcArry(sf::Vector2f) const;
	//return if the object with the givin position is in the vector 

	void manageGame();
	void initilize();//initilize the tools of the game
	void putNew();//putting the players in their start place 
	bool play();//the main function of the game
	void toPlay();//the loop of the levels

	bool begin();//the start screens
	void end();//restart and end the game
	void checkExit();

	void removeMe(DynamicObject *);
	void removeCell(int);

	void resetm_counter_time_poison();
	void reset_counter_time_health();

private:
	std::vector<DynamicObject*> m_ghosts;//the user
	PacMan* m_pacman;//the players
	Board m_board;//the board
	Menu m_menu;

	sf::Texture m_background;
	sf::Texture m_play;
	sf::Texture m_exit;

	sf::Clock m_counter_time_health;//count time to the health cookie
	sf::Clock m_counter_time_poison;//count time to the poison cookie
	sf::Clock m_timer;//the main timer of the game

	sf::Music m_music;
};
int random(int);//random a number from 0 to the givin limit

