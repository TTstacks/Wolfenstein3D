#ifndef OBJECTS_H_
#define OBJECTS_H_
#include "../Object/Object.h"
#include "../GameData/GameData.h"
#include "../RenderableObjects/RenderableObjects.h"
#include "../Player/Player.h"
#include "../RenderableObjects/RenderableObjects.h"
#include "../RenderableObject/RenderableObject.h"
#include "../PickableItem/PickableItem.h"
#include "../PickableHealth/PickableHealth.h"
#include "../PickableScore/PickableScore.h"
#include "../PickableWeapon/PickableWeapon.h"
#include "../NotPickableItem/NotPickableItem.h"
#include "../Enemies/Enemies.h"
#include <memory>
#include <list>

class Objects
{
public:
    Objects(std::shared_ptr<GameData> gameData, Player& player, Enemies& enemies);
    void Update(Player& player, RenderableObjects& renderableObjects, bool& renderYellowWarning);
private:
    std::list<Object> objectsData;
    std::shared_ptr<GameData> gameData;
};

#endif