// ======================include_and_using=============================
#pragma once
#include "ResourceManager.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Menu
{
public:
	//=======================constructors_and_distrustor===================
	Menu();
	~Menu();

	void createMenu(float, float);
	void drawMenu(sf::RenderWindow & window) const;
	int checkButton(sf::Event&);
	//=======================local_function================================
private:
	//=======================object_and_data_members=====================
	std::vector<sf::Sprite> m_sprite;
	std::vector<sf::Texture> m_textur;
};

