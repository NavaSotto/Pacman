#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager& instance();
	sf::Texture getPicture(std::string picture);
private:
	ResourceManager();
	ResourceManager(const ResourceManager&);
	std::map<std::string,sf::Texture> m_texture;
	sf::Texture createTexture(std::string picture);
};

