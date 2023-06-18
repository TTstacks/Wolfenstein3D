#include "SS.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/texture_settings.h"
#include "../WorldMap/WorldMap.h"
#include <cmath>
#include <iostream>

SS::SS(std::shared_ptr<GameData> gameData, Object& object, Player& player)
    : Enemy(gameData, object, player, 100, 100, Animation(true, 5, 0.1f), Animation(false, 3, 0.2f), Animation(false, 4, 0.08f), Animation(false, 2, 0.3f)), shootCounter(0), shootNumber(0), dodgeVelocity(0, 0), randAngleIndex(0), angleAxis(0)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void SS::Update()
{
    float x = this->object.position.x - this->player.GetPosition().x;
    float y = this->object.position.y - this->player.GetPosition().y;
    bool playerHitted = this->PlayerHitted();
    if(playerHitted && this->enemyState != EnemyState::DEAD) this->enemyState = EnemyState::DAMAGED;
    if(this->enemyState != EnemyState::DODGE) this->shootingClock.restart();
    int angleIndex = GetAngleIndex();

    if(this->enemyState == EnemyState::DEFAULT)
    {
        this->object.sprite.setTextureRect(sf::IntRect(angleIndex * texture_size, 0, texture_size, texture_size));
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
            this->enemyState = EnemyState::DODGE;
            this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Angles"));
        }
    }
    else if(this->enemyState == EnemyState::SHOOT)
    {
        this->shootingAnimation.Animate(0, 2);
        if(this->shootingAnimation.GetCurrentFrameIterator() == 2 && this->shootingAnimation.AnimationFrameChanged()) 
        {
            this->player.health -= std::rand() % 40;
            this->shootCounter++;
        }
        this->object.sprite.setTextureRect(this->shootingAnimation.GetAnimationFrame());
        if(this->shootCounter == this->shootNumber && this->shootingAnimation.GetCurrentFrameIterator() != 2) 
        {
            this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Angles"));
            this->enemyState = EnemyState::DODGE;
        }
    }
    else if(this->enemyState == EnemyState::DODGE)
    {
        if(this->shootingClock.getElapsedTime().asSeconds() > 3.f)
        {
            this->enemyState = EnemyState::SHOOT;
            this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Shooting"));
            this->shootNumber = rand() % 2 + 1;
            this->shootCounter = 0;
            this->shootingClock.restart();
        }
        if(this->randomMovementClock.getElapsedTime().asSeconds() > 2.5f)
        {    
            this->SetDodgeVelocity();
            if(std::abs(x) >= std::abs(y)) this->angleAxis = 2;
            else this->angleAxis = 0;
            this->randomMovementClock.restart();
        }
        while(WorldMap::GetElement(static_cast<size_t>(this->object.position.x + dodgeVelocity.x), static_cast<size_t>(this->object.position.y + dodgeVelocity.y)))
        {
            if(std::abs(x) >= std::abs(y)) this->angleAxis = 2;
            else this->angleAxis = 0;
            this->SetDodgeVelocity();
        }
        this->object.position.x += dodgeVelocity.x;
        this->object.position.y += dodgeVelocity.y;
        this->walkingAnimation.Animate(0, 4);
        int rectTop = this->walkingAnimation.GetAnimationFrame().top;
        int currentAngleIndex = (angleIndex + this->angleAxis + (this->randAngleIndex - 2)) % 8;
        this->object.sprite.setTextureRect(sf::IntRect(currentAngleIndex * texture_size, rectTop, texture_size, texture_size));
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

int SS::GetAngleIndex()
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
    return (static_cast<int>(angle) + 1) % 8;
}

void SS::SetDodgeVelocity()
{
    float x = this->object.position.x - this->player.GetPosition().x;
    float y = this->object.position.y - this->player.GetPosition().y;
    this->randAngleIndex = rand() % 2 + 2;
    if(this->randAngleIndex == 3) this->randAngleIndex = 6;
    float v = 0.003f;
    if(this->randAngleIndex == 2)
    {
        if(std::abs(x) < std::abs(y))
        {
            dodgeVelocity.y = 0.f;
            dodgeVelocity.x = -v;
        }
        else
        {
            dodgeVelocity.y = -v;
            dodgeVelocity.x = 0.f;
        }
    }
    else if(this->randAngleIndex == 6)
    {
        if(std::abs(x) < std::abs(y))
        {
            dodgeVelocity.y = 0.f;
            dodgeVelocity.x = v;
        }
        else
        {
            dodgeVelocity.y = v;
            dodgeVelocity.x = 0.f;
        }
    }
}