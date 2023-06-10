#ifndef PICKABLEHEALTH_H_
#define PICKABLEHEALTH_H_
#include "../PickableItem/PickableItem.h"

class PickableHealth : public PickableItem
{
public:
    PickableHealth(int health);
    void Update(Player& player, bool& renderable) final;
private:
    int health;
};
#endif