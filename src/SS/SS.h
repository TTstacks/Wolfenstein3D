#ifndef SS_H_
#define SS_H_
#include "../Enemy/Enemy.h"

class SS : public Enemy
{
public:
    SS(std::shared_ptr<GameData> gameData, Object& object, Player& player);
    void Update() final;
private:
    sf::Clock damagedClock;
};
#endif