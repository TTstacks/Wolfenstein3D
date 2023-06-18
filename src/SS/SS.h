#ifndef SS_H_
#define SS_H_
#include "../Enemy/Enemy.h"

class SS : public Enemy
{
public:
    SS(std::shared_ptr<GameData> gameData, Object& object, Player& player);
    void Update() final;
private:
    int GetAngleIndex();
    void SetDodgeVelocity();
private:
    sf::Clock damagedClock;
    sf::Clock randomMovementClock;
    sf::Clock shootingClock;
    sf::Vector2f dodgeVelocity;
    int shootCounter;
    int shootNumber;
    int randAngleIndex;
    int angleAxis;
};
#endif