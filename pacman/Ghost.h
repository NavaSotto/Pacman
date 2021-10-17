#pragma once
#include "DynamicObject.h"

class Ghost :public DynamicObject
{
public:
	Ghost(sf::Vector2f = { 0,0 });

	//double dispatch 
	//collide active with active
	virtual void collide(DynamicObject*, Controller&);
	virtual void collide(PacMan*, Controller&);
	virtual void collide(Ghost*, Controller&);
	//collide active with passive
	virtual void collide(StaticObject*, Controller&, Board&, sf::Vector2f);

	virtual void cookieCrash(float, Controller&) {};
	//Locates the ghost
	virtual void makePosition(Board &, Controller&);
	void PutInPlace(int, Board &, Controller&);
};
