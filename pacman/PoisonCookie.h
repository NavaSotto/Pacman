#pragma once
#include "Cookies.h"

class PoisonCookie :public Cookies
{
public:
	static float m_speedIncreased;

	PoisonCookie(char c, sf::Vector2f place = { 0,0 });
	virtual ~PoisonCookie();

	void createColor(char c);

};
