#include "SS.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/texture_settings.h"
#include <cmath>

SS::SS(std::shared_ptr<GameData> gameData, Object& object, Player& player)
    : Enemy(gameData, object, player, 100, 100, Animation(true, 5), Animation(false, 3), Animation(false, 4, 0.08f), Animation(false, 2, 0.3f))
{
}

void SS::Update()
{
    bool playerHitted = this->PlayerHitted();
    if(playerHitted && this->enemyState != EnemyState::DEAD) this->enemyState = EnemyState::DAMAGED;
    int angleIndex = GetAngleIndex();
    if(this->enemyState == EnemyState::DEFAULT)
    {
        int rectLeft = (static_cast<int>(angleIndex) + 1) % 8;
        this->object.sprite.setTextureRect(sf::IntRect(rectLeft * texture_size, 0, texture_size, texture_size));
    }
    else if(this->enemyState == EnemyState::DAMAGED)
    {
        if(playerHitted)
        {
            this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Damaged"));
            this->damagedAnimation.Animate(0, 1);
            this->damagedClock.restart();
            this->health -= this->player.weapons.GetCurrentWeaponReference().GetDamage();
            this->object.sprite.setTextureRect(this->damagedAnimation.GetAnimationFrame());
            if(this->health <= 0) 
            {
                this->enemyState = EnemyState::DEAD;
                this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Dying"));
                this->object.sprite.setTextureRect(this->dyingAnimation.GetAnimationFrame());
            }
        }
        else if(this->damagedClock.getElapsedTime().asSeconds() < 0.3f)
        {
            this->damagedAnimation.Animate(0, 1);
            this->object.sprite.setTextureRect(this->damagedAnimation.GetAnimationFrame());
        }
        else
        {
            this->enemyState = EnemyState::DEFAULT;
            this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Angles"));
        }
    }
    else if(this->enemyState == EnemyState::SHOOT)
    {
        this->shootingAnimation.Animate(0, 2);
        this->object.sprite.setTextureRect(this->shootingAnimation.GetAnimationFrame());
        if(this->shootingAnimation.GetCurrentFrameIterator() == 2 && this->shootingAnimation.AnimationFrameChanged()) this->player.health -= std::rand() % 40;
    }
    else if(this->enemyState == EnemyState::DODGE)
    {
        
    }
    else if(this->enemyState == EnemyState::CHASE)
    {
    
    }
    else if(this->enemyState == EnemyState::DEAD)
    {
        if(this->dyingAnimation.GetCurrentFrameIterator() != 3) 
        {
            this->dyingAnimation.Animate(0, 3);
            this->object.sprite.setTextureRect(this->dyingAnimation.GetAnimationFrame());
        }
    }
}

int SS::GetAngle()
{
    float x = this->object.position.x - this->player.GetPosition().x;
    float y = this->object.position.y - this->player.GetPosition().y;
    float angle = std::atan2(y, x);
    if(angle < 0) angle += pi * 2;
    angle = pi * 2 - angle;
    
    for(int i = 1; i <= 8; i++)
    {
        float v = i * pi / 4;
        if(i == 8)
        {
            if((angle > v - pi / 8 && angle <= pi * 2) || (angle > 0.f && angle <= pi / 8)) angle = i - 1;
            break;
        }
        if(angle > v - pi / 8 && angle <= v + pi / 8)
        {
            angle = i - 1; break;
        }
    }   
    return angle;
}