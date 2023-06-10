#ifndef WEAPONS_H_
#define WEAPONS_H_
#include <unordered_map>
#include <memory>
#include <string>
#include "../GameData/GameData.h"
#include "../Weapon/Weapon.h"

class Weapons
{
public:
	Weapons(std::shared_ptr<GameData> gameData);
	void AddWeapon(std::string weaponName, int bullets);
	void ChooseWeapon();
	void RemoveEmptyWeapon();
	Weapon& GetCurrentWeaponReference();
private:
	std::shared_ptr<GameData> gameData;
	std::unordered_map<std::string, Weapon> weaponsData;
	std::unordered_map<std::string, Weapon>::iterator weaponIterator;
};

#endif