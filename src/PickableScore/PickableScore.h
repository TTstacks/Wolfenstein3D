#ifndef PICKABLESCORE_H_
#define PICKABLESCORE_H_
#include "../PickableItem/PickableItem.h"

class PickableScore : public PickableItem
{
public:
    PickableScore(int score);
    void Update(Player& player, bool& renderable) final;
private:
    int score;
};
#endif