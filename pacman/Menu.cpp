
// ======================include_and_using=============================​
#include "Menu.h"
#include <thread>
#include <conio.h>
const sf::Vector2f SIZE_BUTTON(170.f, 170.f);
//=======================constructors_and_distrustor===================
Menu::Menu()
{
}
//---------------------------------------------------------------------
Menu::~Menu()
{
}
void Menu::createMenu(float width, float length)
{
	m_sprite.resize(4);
	m_textur.resize(4);

	m_textur[0] = ResourceManager::instance().getPicture("openScreen");
	m_textur[1] = ResourceManager::instance().getPicture("play");
	m_textur[2] = ResourceManager::instance().getPicture("exit");
	m_textur[3] = ResourceManager::instance().getPicture("openPacman");

	m_textur[0].setSmooth(true);
	m_sprite[0].setTexture(m_textur[0]);
	m_sprite[0].scale(width / m_textur[0].getSize().x, length / m_textur[0].getSize().y);

	m_sprite[1].setTexture(m_textur[1]);
	m_sprite[1].setPosition(width / 1.5, length / 13);
	m_sprite[1].scale(SIZE_BUTTON.x / m_textur[1].getSize().x, SIZE_BUTTON.y / m_textur[1].getSize().y);

	m_sprite[2].setTexture(m_textur[2]);
	m_sprite[2].setPosition(width / 12, length / 13);
	m_sprite[2].scale(SIZE_BUTTON.x / m_textur[2].getSize().x, SIZE_BUTTON.y / m_textur[2].getSize().y);

	m_sprite[3].setTexture(m_textur[3]);
	m_sprite[3].setPosition(width / 19, length / 5);
	m_sprite[3].scale(630.f / m_textur[3].getSize().x, 550.f / m_textur[3].getSize().y);
}
//=======================local_function================================

//---------------------------------------------------------------------
void Menu::drawMenu(sf::RenderWindow & window) const
{
	for (int i = 0; i < m_sprite.size(); i++)
		window.draw(m_sprite[i]);
}

int Menu::checkButton(sf::Event & event)
{
	if (m_sprite[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return 1;
	if (m_sprite[2].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return 2;
}
