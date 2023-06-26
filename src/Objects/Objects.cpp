#include "Objects.h"
#include "../SS/SS.h"


Objects::Objects(std::shared_ptr<GameData> gameData, Player& player, Enemies& enemies)
    : gameData(gameData)
{
    auto p1 = std::shared_ptr<PickableItem>(new NotPickableItem());
    auto p2 = std::shared_ptr<PickableItem>(new PickableHealth(100));
    auto p3 = std::shared_ptr<PickableItem>(new PickableWeapon("ChainGun", 100));
    auto p4 = std::shared_ptr<PickableItem>(new PickableScore(10000));
    auto p5 = std::shared_ptr<PickableItem>(new PickableWeapon("MachineGun", 15));
    auto p6 = std::shared_ptr<PickableItem>(new PickableWeapon("Pistol", 15));
    objectsData.push_back(Object(sf::Vector2f(1.5f, 1.5f), gameData->resourceManager.GetTexture("Statue"), p1));
    objectsData.push_back(Object(sf::Vector2f(1.5f, 2.f), gameData->resourceManager.GetTexture("Knight"), p1));
    objectsData.push_back(Object(sf::Vector2f(1.5f, 2.5f), gameData->resourceManager.GetTexture("Table"), p1, 20.f));
    objectsData.push_back(Object(sf::Vector2f(2.5f, 2.5f), gameData->resourceManager.GetTexture("Health Head"), p2));
    objectsData.push_back(Object(sf::Vector2f(17.5f, 6.5f), gameData->resourceManager.GetTexture("MachineGun Ammo"), p3));
    objectsData.push_back(Object(sf::Vector2f(17.5f, 5.5f), gameData->resourceManager.GetTexture("ChainGun Ammo"), p5));
    objectsData.push_back(Object(sf::Vector2f(17.5f, 4.5f), gameData->resourceManager.GetTexture("Magazine"), p6));
    objectsData.push_back(Object(sf::Vector2f(16.5f, 3.5f), gameData->resourceManager.GetTexture("SS/Angles"), p1, 0.f, 64, 64));
    enemies.Add(new SS(this->gameData, objectsData.back(), player));
}

void Objects::Update(Player& player, RenderableObjects& renderableObjects, bool& renderYellowWarning)
{
    objectsData.remove_if([](Object& object){return object.removable;});
    for(auto& object : objectsData) object.Update(player, renderableObjects, renderYellowWarning);
}