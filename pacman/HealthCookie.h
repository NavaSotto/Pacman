#pragma once
#include "Cookies.h"

class HealthCookie :public Cookies
{
public:
	static float m_SpeedIncrease;

	HealthCookie(char c, sf::Vector2f place = { 0,0 });
	virtual ~HealthCookie();

	void createColor(char c);

};
