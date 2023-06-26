#include "ResourceManager.h"

void ResourceManager::AddTexture(std::string_view texturePath, std::string_view textureName)
{
	if (this->textureData.contains(textureName.data())) return;
	this->textureData[textureName.data()].loadFromFile(texturePath.data());
}

sf::Texture& ResourceManager::GetTexture(std::string_view textureName)
{
	return this->textureData.at(textureName.data());
}

void ResourceManager::AddFont(std::string_view fontPath, std::string_view fontName)
{
	if (this->fontData.contains(fontName.data())) return;
	this->textureData[fontName.data()].loadFromFile(fontPath.data());
}

sf::Font& ResourceManager::GetFont(std::string_view fontName)
{
	return this->fontData.at(fontName.data());
}