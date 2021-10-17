#pragma once
#include "Object.h"
#include "StaticObject.h"
#include "Wall.h"
#include "HealthCookie.h"
#include "PoisonCookie.h"
#include "Cookies.h"


class Ghost;
class PacMan;
class Controller;
class Board;

class DynamicObject :public Object
{


public:
	//static value
	static float speed;//all the players have the same speed in the beginning.

					   //constructor
	DynamicObject(sf::Vector2f = { 0,0 });

	//set/get functions
	void setPosition(sf::Vector2f);
	float getSpeed() const;//get the current speed of the player
	virtual void setSpeed(float) {};//virtual function that change the speed only on the types pacmans
	int getLastPos() const;
	int getLastSide() const;

	//move
	virtual void move(float, Controller&, Board&);
	virtual int moving(Controller&) = 0;

	//collides
	virtual void collide(StaticObject*, Controller&, Board&, sf::Vector2f) = 0;//collide active whith passive
																				//double dispatch 
	virtual void collide(DynamicObject*, Controller&) = 0;
	virtual void collide(PacMan*, Controller&) = 0;
	virtual void collide(Ghost*, Controller&) = 0;
	//eat cookie
	virtual void cookieCrash(float, Controller&) = 0;

	//lacating
	virtual void makePosition(Board &, Controller&) = 0;

protected:
	float m_speed;//the speed of the player
	int m_lastPos = 0;//save the last change direction 
	int m_last_side = 0;//save from which side the player came to the wall
};
