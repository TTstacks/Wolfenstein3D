#include "Enemy.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/texture_settings.h"

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
