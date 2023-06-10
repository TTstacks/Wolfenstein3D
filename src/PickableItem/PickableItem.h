#ifndef PICKABLEITEM_H_
#define PICKABLEITEM_H_
#include "../Player/Player.h"

class PickableItem
{
public:
    PickableItem();
    virtual void Update(Player& player, bool& renderable) = 0;
};
#endif