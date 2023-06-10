#ifndef ENEMIES_H_
#define ENEMIES_H_
#include <vector>
#include "../Enemy/Enemy.h"

class Enemies
{
public:
    Enemies();
    ~Enemies();
    void Add(Enemy* enemy);
    void Update();
private:
    std::vector<Enemy*> enemiesData;
};
#endif