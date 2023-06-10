#include "Object.h"


Object::Object(sf::Vector2f position, sf::Texture& texture, std::shared_ptr<PickableItem> pickableItem, float shiftY, float width, float height)
    : position(position), sprite(texture), removable(false), pickableItem(pickableItem)
{
    if(width == 0.f || height == 0.f) sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2 - shiftY);
    else sprite.setOrigin(width / 2, height / 2 - shiftY);
}

/*void Object::Update(float playerAngle, sf::Vector2f playerPosition, RenderableObjects& renderableObjects)
{
    float x = position.x - playerPosition.x;
    float y = position.y - playerPosition.y;
    const float cosA = std::cos(playerAngle);
    const float sinA = std::sin(playerAngle);
    float tempX = cosA * y - sinA * x;
    float tempY = cosA * x + sinA * y;
    x = std::move(tempX); y = std::move(tempY);
    const float windowX = (x * projection_coefficient / y) + ray_number / 2;
    const float scale = projection_coefficient / (y * 100.f);
    sprite.setScale(scale, scale);
    if(windowX + sprite.getGlobalBounds().width / 2 >= 0 && windowX - sprite.getGlobalBounds().width / 2 < ray_number && y > 0)
    {
        RenderableObject renderableObject;
        sprite.setPosition(windowX * wall_width, half_window_height);
        renderableObject.distance = y;
        renderableObject.sprite = sprite;
        renderableObjects.AddRenderableObject(renderableObject);
    }
}*/