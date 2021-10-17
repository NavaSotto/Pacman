#pragma once
#include "StaticObject.h"

class Wall :public StaticObject
{
public:
	Wall(char c, sf::Vector2f = { 0,0 });
	virtual ~Wall();
};