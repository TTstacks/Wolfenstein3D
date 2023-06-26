#include "PickableHealth.h"

PickableHealth::PickableHealth(int health)
    : health(health)
{

}

void PickableHealth::Update(Player& player, bool& renderable)
{
    player.health += this->health;
    player.health = std::min(player.health, 100);
    renderable = true;
}