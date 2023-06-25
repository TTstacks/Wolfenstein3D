#ifndef WALLS_H_
#define WALLS_H_
#include "SFML/Graphics.hpp"
#include <vector>
#include "../RenderableObject/RenderableObject.h"
#include "../GameData/GameData.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/texture_settings.h"
#include "../RenderableObjects/RenderableObjects.h"
#include "../WorldMap/WorldMap.h"

class Walls
{
public:
    Walls(std::shared_ptr<GameData> gameData);
    void Update(float playerAngle, sf::Vector2f playerPosition, RenderableObjects& RenderableObjects);
    const float& GetWallDistance(size_t index);
private:
    std::shared_ptr<GameData> gameData;
    std::vector<float> wallDistances;
};
#endif