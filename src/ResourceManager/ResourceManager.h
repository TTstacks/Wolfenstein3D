#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_
#include <map>
#include <string>
#include <string_view>
#include "SFML/Graphics.hpp"

class ResourceManager
{
public:
	void AddTexture(std::string_view texturePath, std::string_view textureName);
	sf::Texture& GetTexture(std::string_view textureName);
private:
	std::map<std::string, sf::Texture> textureData;
};
#endif