#ifndef ENEMY_H_
#define ENEMY_H_
#include "../GameData/GameData.h"
#include "../Object/Object.h"
#include "../Player/Player.h"
#include "../Animation/Animation.h"

class Enemy
{
public:
    Enemy(std::shared_ptr<GameData> gameData, Object& object, Player& player, int health, int damage, Animation walkingAnimation, Animation shootingAnimation, Animation dyingAnimation, Animation damagedAnimation);
    virtual void Update() = 0;
protected:
    bool PlayerHitted();
    bool CanSeePlayer(Player& player);
protected:
    enum EnemyState
    {
        SHOOT,
        DODGE,
        CHASE,
        DEAD,
        DAMAGED,
        DEFAULT
    };    
protected:
    EnemyState enemyState;
    std::shared_ptr<GameData> gameData;
    Object& object;
    Player& player;
    int health;
    int damage;
    Animation walkingAnimation;
    Animation shootingAnimation;
    Animation dyingAnimation;
    Animation damagedAnimation;
};
#endif