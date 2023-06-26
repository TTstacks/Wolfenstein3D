#ifndef OBJECT_H_
#define OBJECT_H_
#include "SFML/Graphics.hpp"
#include "../RenderableObjects/RenderableObjects.h"
#include "../RenderableObject/RenderableObject.h"
#include "../PickableItem/PickableItem.h"
#include "../Walls/Walls.h"
#include <memory>

class Object
{
public:
    Object(sf::Vector2f position, sf::Texture& texture, std::shared_ptr<PickableItem> pickableItem, float shiftY = 0.f, float width = 0.f, float height = 0.f);
    void Update(Player& player, RenderableObjects& renderableObjects, bool& renderYellowWarning);
public:
    bool removable;
    sf::Vector2f position;
    sf::Sprite sprite;
    std::shared_ptr<PickableItem> pickableItem;
};
#endif