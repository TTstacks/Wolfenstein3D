#include "Object.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/game_settings.h"
#include "../Constants/texture_settings.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Object::Object(sf::Vector2f position, sf::Texture& texture, std::shared_ptr<PickableItem> pickableItem, float shiftY, float width, float height)
    : position(position), sprite(texture), removable(false), pickableItem(pickableItem)
{
    if(width == 0.f || height == 0.f) sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2 - shiftY);
    else sprite.setOrigin(width / 2, height / 2 - shiftY);
}

void Object::Update(Player& player, RenderableObjects& renderableObjects, bool& renderYellowWarning)
{
    float x = position.x - player.GetPosition().x;
    float y = position.y - player.GetPosition().y;
    float distance = std::hypot(x, y);
    const float cosA = std::cos(player.GetAngle());
    const float sinA = std::sin(player.GetAngle());
    float tempX = cosA * y - sinA * x;
    float tempY = cosA * x + sinA * y;
    x = std::move(tempX); y = std::move(tempY);
    const float windowX = (x * projection_coefficient / y) + ray_number / 2;
    const float scale = projection_coefficient / (y * 100.f);
    sprite.setScale(scale, scale);
    if(distance <= 0.3f)
    {
        pickableItem->Update(player, this->removable);
        if(this->removable) renderYellowWarning = true;
    }
    if(windowX + sprite.getGlobalBounds().width / 2 >= 0 && windowX - sprite.getGlobalBounds().width / 2 < ray_number && y > 0)
    {
        RenderableObject renderableObject;
        sprite.setPosition(windowX * wall_width, half_window_height);
        renderableObject.distance = y;
        renderableObject.sprite = sprite;
        renderableObjects.AddRenderableObject(renderableObject);
    
    }
}