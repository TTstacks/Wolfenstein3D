#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<GameData> gameData, Object &object, Player &player, int health, int damage, Animation walkingAnimation, Animation shootingAnimation, Animation dyingAnimation, Animation damagedAnimation)
 : enemyState(EnemyState::DEFAULT), gameData(gameData), object(object), player(player), health(health), damage(damage), walkingAnimation(walkingAnimation), shootingAnimation(shootingAnimation), dyingAnimation(dyingAnimation), damagedAnimation(damagedAnimation)
{

}
