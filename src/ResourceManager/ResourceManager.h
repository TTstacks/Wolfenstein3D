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
	void AddFont(std::string_view fontPath, std::string_view fontName);
	sf::Font& GetFont(std::string_view fontName);
private:
	std::map<std::string, sf::Texture> textureData;
	std::map<std::string, sf::Font> fontData;
};
#endif