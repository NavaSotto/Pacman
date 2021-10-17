#pragma once
#include "DynamicObject.h"
#include <SFML/Audio.hpp>

class PacMan :public DynamicObject
{


public:
	PacMan(int color, sf::Vector2f = { 0,0 }); //Default constructor

	int getLives() const;
	void setLives(int);

	//Collide of double dispatch - checks collide of active with active
	virtual void collide(DynamicObject*, Controller&);
	virtual void collide(PacMan*, Controller&);
	virtual void collide(Ghost*, Controller&);

	//Checks collide of active with passive
	virtual void collide(StaticObject*, Controller&, Board&, sf::Vector2f);

	//Locates the pacman as close to the center
	virtual void makePosition(Board &, Controller&);

	int getScore() const;
	void setScore(int);
	virtual void setSpeed(float);

	//Returns a value between 0 to 3 to know where to move to
	virtual int moving(Controller&);

	//A virtual check if crashed with cookie function
	virtual void cookieCrash(float, Controller&);


protected:
	int m_lives;
	int m_score = 0;
	sf::SoundBuffer m_sound; //A sound which is played when eats a cookie
	sf::Sound m_eatSound;
};

