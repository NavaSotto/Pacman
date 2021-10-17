#pragma once
#include "Ghost.h"

class RandomGhost :public Ghost
{
public:
	RandomGhost(int color, sf::Vector2f = { 0,0 });

	//Returns a value between 0 to 3 to know where to move to
	virtual int moving(Controller&);
};