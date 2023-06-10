#ifndef GAMEDATA_H_
#define GAMEDATA_H_
#include "../ResourceManager/ResourceManager.h"
#include "SFML/Graphics.hpp"

struct GameData
{
	sf::RenderWindow window;
	ResourceManager resourceManager;
};
#endif