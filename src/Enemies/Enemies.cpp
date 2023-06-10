#include "Enemies.h"

Enemies::Enemies()
{

}

Enemies::~Enemies()
{
    for(auto& enemy : this->enemiesData) delete enemy;
}

void Enemies::Add(Enemy* enemy)
{
    this->enemiesData.push_back(enemy);
}

void Enemies::Update()
{
    for(auto& enemy : enemiesData)
    {
        enemy->Update();
    }
}