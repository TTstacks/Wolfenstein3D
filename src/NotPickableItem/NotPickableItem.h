#ifndef NOTPICKABLEITEM_H_
#define NOTPICKABLEITEM_H_
#include "../PickableItem/PickableItem.h"

class NotPickableItem : public PickableItem
{
public:
    NotPickableItem();
    void Update(Player& player, bool& renderable) final;
};
#endif