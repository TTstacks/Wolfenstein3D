#include "Enemy.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/texture_settings.h"
#include "../WorldMap/WorldMap.h"
#include <cmath>

Enemy::Enemy(std::shared_ptr<GameData> gameData, Object &object, Player &player, int health, int damage, Animation walkingAnimation, Animation shootingAnimation, Animation dyingAnimation, Animation damagedAnimation)
 : enemyState(EnemyState::DEFAULT), gameData(gameData), object(object), player(player), health(health), damage(damage), walkingAnimation(walkingAnimation), shootingAnimation(shootingAnimation), dyingAnimation(dyingAnimation), damagedAnimation(damagedAnimation)
{

}

bool Enemy::PlayerHitted()
{
    const float objectLeftSide = this->object.sprite.getPosition().x / wall_width - this->object.sprite.getGlobalBounds().width / 2.f;
    const float objectRightSide = this->object.sprite.getPosition().x / wall_width + this->object.sprite.getGlobalBounds().width / 2.f;
    return objectLeftSide <= half_ray_number && half_ray_number <= objectRightSide && this->player.weapons.GetCurrentWeaponReference().isShooting();
}

bool Enemy::CanSeePlayer(Player& player)
{
    float dx = this->object.position.x - player.GetPosition().x;
    float dy = this->object.position.y - player.GetPosition().y;
    sf::Vector2f unitStepSize(std::hypot(1.f, dy / dx), std::hypot(1.f, dx / dy));
    sf::Vector2i objectCeilPosition(this->object.position);
    sf::Vector2i playerCeilPosition(player.GetPosition());
    sf::Vector2f totalStepSize;
    sf::Vector2i ceilStep;
    if(dx < 0)
    {
        ceilStep.x = 1;
        totalStepSize.x = (1.f + static_cast<float>(objectCeilPosition.x) - this->object.position.x) * unitStepSize.x;
    }
    else
    {
        ceilStep.x = -1;
        totalStepSize.x = (this->object.position.x - static_cast<float>(objectCeilPosition.x)) * unitStepSize.x;
    }
    if(dy < 0)
    {
        ceilStep.y = 1;
        totalStepSize.y = (1.f + static_cast<float>(objectCeilPosition.y) - this->object.position.y) * unitStepSize.y;
    }
    else
    {
        ceilStep.y = -1;
        totalStepSize.y = (this->object.position.y - static_cast<float>(objectCeilPosition.y)) * unitStepSize.y;
    }
    while(true)
    {
        if(WorldMap::GetElement(objectCeilPosition.x, objectCeilPosition.y)) return false;
        if(objectCeilPosition == playerCeilPosition) return true;
        if(totalStepSize.x < totalStepSize.y)
        {
            totalStepSize.x += unitStepSize.x;
            objectCeilPosition.x += ceilStep.x;
        }
        else
        {
            totalStepSize.y += unitStepSize.y;
            objectCeilPosition.y += ceilStep.y;
        }
    }
}
