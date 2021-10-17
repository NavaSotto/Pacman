#include "ResourceManager.h"


//---------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
}
//---------------------------------------------------------------------

ResourceManager & ResourceManager::instance()
{
	static ResourceManager instance;
	return instance;
}
//---------------------------------------------------------------------
sf::Texture  ResourceManager::createTexture(std::string picture)
{
	sf::Texture texture;
	texture.loadFromFile(picture);
	return texture;
}
sf::Texture  ResourceManager::getPicture(std::string picture)
{
	return m_texture[picture];
}
//---------------------------------------------------------------------
ResourceManager::ResourceManager()
{
	m_texture.insert(std::make_pair("openScreen", createTexture("openScreen.png")));
	m_texture.insert(std::make_pair("play", createTexture("play.png")));
	m_texture.insert(std::make_pair("exit", createTexture("exit.png")));
	m_texture.insert(std::make_pair("background", createTexture("background.png")));
	m_texture.insert(std::make_pair("pacman", createTexture("pacman.png")));
	m_texture.insert(std::make_pair("blueWall", createTexture("blueWall.png")));
	m_texture.insert(std::make_pair("redWall", createTexture("redWall.png")));
	m_texture.insert(std::make_pair("greenWall", createTexture("greenWall.png")));
	m_texture.insert(std::make_pair("ghost", createTexture("ghost.png")));
	m_texture.insert(std::make_pair("standardBlueCookie", createTexture("standardBlueCookie.png")));
	m_texture.insert(std::make_pair("standardRedCookie", createTexture("standardRedCookie.png")));
	m_texture.insert(std::make_pair("standardGreenCookie", createTexture("standardGreenCookie.png")));
	m_texture.insert(std::make_pair("healthyBlueCookie", createTexture("healthyBlueCookie.png")));
	m_texture.insert(std::make_pair("healthyRedCookie", createTexture("healthyRedCookie.png")));
	m_texture.insert(std::make_pair("healthyGreenCookie", createTexture("healthyGreenCookie.png")));
	m_texture.insert(std::make_pair("poisonedBlueCookie", createTexture("poisonedBlueCookie.png")));
	m_texture.insert(std::make_pair("poisonedRedCookie", createTexture("poisonedRedCookie.png")));
	m_texture.insert(std::make_pair("poisonedGreenCookie", createTexture("poisonedGreenCookie.png")));
	m_texture.insert(std::make_pair("gameOver", createTexture("gameOver.png")));
}
//---------------------------------------------------------------------
ResourceManager::ResourceManager(const ResourceManager &other)
{
}