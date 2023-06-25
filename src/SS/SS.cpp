#include "SS.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/texture_settings.h"
#include "../WorldMap/WorldMap.h"
#include <cmath>

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
    bool canSee = this->CanSeePlayer(this->player);
    if(playerHitted && this->enemyState != EnemyState::DEAD) this->enemyState = EnemyState::DAMAGED;
    if(this->enemyState != EnemyState::DODGE) this->dodgeClock.restart();
    if(this->enemyState != EnemyState::CHASE) this->chaseClock.restart();
    if(this->enemyState == EnemyState::SHOOT && !this->object.playerCanInteract) 
    {
        this->enemyState = EnemyState::DEFAULT;
        this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Angles"));
    }
    int angleIndex = GetAngleIndex();

    if(this->enemyState == EnemyState::DEFAULT)
    {
        this->object.sprite.setTextureRect(sf::IntRect(angleIndex * texture_size, 0, texture_size, texture_size));
        if(canSee) this->enemyState = EnemyState::CHASE;
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
        this->targetPosition = this->player.GetPosition();
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
            this->enemyState = EnemyState::CHASE;
        }
    }
    else if(this->enemyState == EnemyState::DODGE)
    {
        if(this->dodgeClock.getElapsedTime().asSeconds() > 3.f)
        {
            this->enemyState = EnemyState::SHOOT;
            this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Shooting"));
            this->shootNumber = rand() % 2 + 1;
            this->shootCounter = 0;
            this->dodgeClock.restart();
        }
        if(this->randomMovementClock.getElapsedTime().asSeconds() > 2.5f)
        {    
            this->SetDodgeVelocity();
            if(std::abs(x) >= std::abs(y)) this->angleAxis = 2;
            else this->angleAxis = 0;
            this->randomMovementClock.restart();
        }

        for(int i = -1; i <= 1; i += 2)
        {
            if(WorldMap::GetElement(this->object.position.x + 0.1f * i, this->object.position.y))
            {
                if(this->dodgeVelocity.x == 0.f) this->object.position.x -= 0.1f * i;
                else
                { 
                    this->randAngleIndex = (this->randAngleIndex + 4) % 8;
                    this->dodgeVelocity.x *= -1.f;
                }
            }
            if(WorldMap::GetElement(this->object.position.x, this->object.position.y + 0.1f * i))
            {
                if(this->dodgeVelocity.y == 0.f) this->object.position.y -= 0.1f * i;
                else 
                {
                    this->randAngleIndex = (this->randAngleIndex + 4) % 8;
                    this->dodgeVelocity.y *= -1.f;
                }
            }
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
        if(!canSee) this->enemyState = EnemyState::DEFAULT;
        else if(this->chaseClock.getElapsedTime().asSeconds() < 1.5f)
        {
            sf::Vector2i objectCellPosition(this->object.position);
            sf::Vector2i playerCellPosition(this->player.GetPosition());
            float v = 0.003f;
            int angleAxis = 0;
            sf::Vector2i position;
            position.x = objectCellPosition.x - playerCellPosition.x;
            position.y = objectCellPosition.y - playerCellPosition.y;
            if(objectCellPosition.x != playerCellPosition.x && objectCellPosition.y != playerCellPosition.y)
            {
                if(!WorldMap::GetElement(object.position.x - std::sqrt(v * v / 2.f) * (position.x / abs(position.x)), object.position.y)) object.position.x -= std::sqrt(v * v / 2.f) * (position.x / std::abs(position.x));
                if(!WorldMap::GetElement(object.position.x, object.position.y - std::sqrt(v * v / 2.f) * (position.y / abs(position.y)))) object.position.y -= std::sqrt(v * v / 2.f) * (position.y / std::abs(position.y));
                if(std::abs(position.y) > std::abs(position.x))
                {
                    if((position.x < 0 && position.y < 0) || (position.x > 0 && position.y > 0)) angleAxis = 7;
                    else if(position.x > 0 && position.y < 0 || position.x < 0 && position.y > 0) angleAxis = 1;
                }
                else if(std::abs(position.y) < std::abs(position.x))
                {
                    if((position.x < 0 && position.y > 0) || (position.x > 0 && position.y < 0)) angleAxis = 7;
                    else if(position.x < 0 && position.y < 0 || position.x > 0 && position.y > 0) angleAxis = 1;    
                }
            }
            else if(objectCellPosition.x != playerCellPosition.x && objectCellPosition.y == playerCellPosition.y) this->object.position.x -= v * (position.x / std::abs(position.x));
            else if(objectCellPosition.x == playerCellPosition.x && objectCellPosition.y != playerCellPosition.y) this->object.position.y -= v * (position.y / std::abs(position.y));
            else
            {
                this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Shooting"));
                this->enemyState = EnemyState::SHOOT;
                this->shootNumber = rand() % 2 + 1;
                this->shootCounter = 0;
            }
            this->walkingAnimation.Animate(0, 4);
            int rectTop = this->walkingAnimation.GetAnimationFrame().top;
            this->object.sprite.setTextureRect(sf::IntRect(angleAxis * texture_size, rectTop, texture_size, texture_size));
        }
        else
        {
            this->object.sprite.setTexture(this->gameData->resourceManager.GetTexture("SS/Shooting"));
            this->enemyState = EnemyState::SHOOT;
            this->shootNumber = rand() % 2 + 1;
            this->shootCounter = 0;
            this->chaseClock.restart();
        }
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