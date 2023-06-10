#include "PickableWeapon.h"

PickableWeapon::PickableWeapon(const std::string weaponName, int bullets)
    : weaponName(weaponName), bullets(bullets)
{

}

void PickableWeapon::Update(Player& player, bool& renderable)
{
    player.weapons.AddWeapon(this->weaponName, this->bullets);
    renderable = true;
}