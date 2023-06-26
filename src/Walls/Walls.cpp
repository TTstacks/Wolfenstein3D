#include "Walls.h"
#include <cmath>

Walls::Walls(std::shared_ptr<GameData> gameData)
    : gameData(gameData)
{
}

void Walls::Update(float playerAngle, sf::Vector2f playerPosition, RenderableObjects& renderableObjects)
{
    float wallAngle = playerAngle - half_fov;
    RenderableObject object;
	object.sprite.setTexture(gameData->resourceManager.GetTexture("Wall1"));
    for(size_t i = 0; i < ray_number; i++)
    {
        const float cosAngle = std::cos(wallAngle);
	    const float sinAngle = std::sin(wallAngle);
	    const float tanAngle = std::tan(wallAngle);
	    const float ctnAngle = 1.f / std::tan(wallAngle);
	    const sf::Vector2f unitStepSize = sf::Vector2f(std::hypot(1.f, tanAngle), std::hypot(1.f, ctnAngle));
	    sf::Vector2i playerCeilPosition(playerPosition);
	    sf::Vector2f totalStepSize;
	    sf::Vector2i ceilStep;
	    if (cosAngle < 0)
	    {
	    	ceilStep.x = -1;
	    	totalStepSize.x = (playerPosition.x - static_cast<float>(playerCeilPosition.x)) * unitStepSize.x;
	    }
	    else
	    {
	    	ceilStep.x = 1;
	    	totalStepSize.x = (1.f + static_cast<float>(playerCeilPosition.x) - playerPosition.x) * unitStepSize.x;
	    }
	    if (sinAngle < 0)
	    {
	    	ceilStep.y = -1;
	    	totalStepSize.y = (playerPosition.y - static_cast<float>(playerCeilPosition.y)) * unitStepSize.y;
	    }
	    else
	    {
	    	ceilStep.y = 1;
	    	totalStepSize.y = (1.f + static_cast<float>(playerCeilPosition.y) - playerPosition.y) * unitStepSize.y;
	    }
	    while (true)
	    {
	    	if (totalStepSize.x < totalStepSize.y)
	    	{
	    		object.distance = totalStepSize.x;
	    		totalStepSize.x += unitStepSize.x;
	    		playerCeilPosition.x += ceilStep.x;
	    	}
	    	else
	    	{
	    		object.distance = totalStepSize.y;
	    		totalStepSize.y += unitStepSize.y;
	    		playerCeilPosition.y += ceilStep.y;
	    	}
	    	const int worldMapElement = WorldMap::GetElement(playerCeilPosition.x, playerCeilPosition.y);
	    	if (worldMapElement)
	    	{
				int rectLeft, rectTop = 0, rectHeight = texture_size;
	    		if(totalStepSize.y - unitStepSize.y > totalStepSize.x - unitStepSize.x)
                    rectLeft = (worldMapElement - 1) * texture_size + static_cast<int>((playerPosition.x + object.distance * cosAngle) * texture_wall_size) % texture_wall_size * wall_width;
                else
                    rectLeft = (worldMapElement - 1) * texture_size + static_cast<int>((playerPosition.y + object.distance * sinAngle) * texture_wall_size) % texture_wall_size * wall_width;
			    const float scaleY = projection_coefficient / (object.distance * std::cos(playerAngle - wallAngle) * 100.f);
	    		object.sprite.setScale(1.f, scaleY);
				if(object.sprite.getGlobalBounds().height > window_height) 
				{
					rectHeight = static_cast<int>(texture_size / (static_cast<float>(object.sprite.getGlobalBounds().height) / window_height));
					rectTop = texture_size / 2 - rectHeight / 2;
				}
			    object.sprite.setTextureRect(sf::IntRect(rectLeft, rectTop, wall_width, rectHeight));
				object.sprite.setPosition(i * wall_width, half_window_height - object.sprite.getGlobalBounds().height / 2);
                renderableObjects.AddRenderableObject(object);
	    		break;
	    	}
	    }
        wallAngle += delta_angle;
    }
}