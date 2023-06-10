#include "PickableHealth.h"

PickableHealth::PickableHealth(int health)
    : health(health)
{

}

void PickableHealth::Update(Player& player, bool& renderable)
{
    player.health += this->health;
    renderable = true;
}