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
