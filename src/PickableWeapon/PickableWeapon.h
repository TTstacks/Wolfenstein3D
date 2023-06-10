#ifndef PICKABLEWEAPON_H_
#define PICKABLEWEAPON_H_
#include "../PickableItem/PickableItem.h"
#include <string>

class PickableWeapon : public PickableItem
{
public:
    PickableWeapon(const std::string weaponName, int bullet);
    void Update(Player& player, bool& renderable) final;
private:
    const std::string weaponName;
    int bullets;
};
#endif