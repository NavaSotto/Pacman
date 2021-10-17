#pragma once
#include "Ghost.h"

class SmartGhost :public Ghost
{
public:
	SmartGhost(int color, sf::Vector2f = { 0,0 });
	virtual int moving(Controller&);//return 0-3 where to move
};