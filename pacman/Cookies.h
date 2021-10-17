#pragma once
#include "StaticObject.h"

class Cookies :public StaticObject
{
public:
	static int total;//count how much cookies we have
	static float m_speedIncrease;

	Cookies(char c, sf::Vector2f = { 0,0 });
	virtual ~Cookies();

	void createColor(char c);

};
