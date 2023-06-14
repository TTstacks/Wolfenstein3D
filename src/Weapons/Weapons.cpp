#include "Weapons.h"
#include "SFML/Graphics.hpp"
#include "../ConstantShootingAnimation/ConstantShootingAnimation.h"
#include "../ContinuousShootingAnimation/ContinuousShootingAnimation.h"
#include <iostream>

Weapons::Weapons(std::shared_ptr<GameData> gameData)
	: gameData(gameData)
{
	this->weaponsData.emplace(std::make_pair<std::string, Weapon>(std::string("Knife"), Weapon{new ContinuousShootingAnimation(this->gameData->resourceManager.GetTexture("Knife")), 5}));
	this->weaponIterator = this->weaponsData.begin();
}

void Weapons::AddWeapon(std::string weaponName, int bullets)
{
	if(this->weaponsData.contains(weaponName))
	{
		this->weaponsData[weaponName].AddBullet(bullets);
		return;
	}
	if(weaponName == "Pistol") this->weaponsData.insert(std::make_pair<std::string, Weapon>(std::string("Pistol"), Weapon{new ContinuousShootingAnimation(this->gameData->resourceManager.GetTexture("Pistol")), 10, bullets}));
	else if(weaponName == "ChainGun") this->weaponsData.insert(std::make_pair<std::string, Weapon>(std::string("ChainGun"), Weapon{new ConstantShootingAnimation(this->gameData->resourceManager.GetTexture("Chaingun")), 15, bullets}));
	else if(weaponName == "MachineGun") this->weaponsData.insert(std::make_pair<std::string, Weapon>(std::string("MachineGun"), Weapon{new ConstantShootingAnimation(this->gameData->resourceManager.GetTexture("MachineGun")), 20, bullets}));

}

void Weapons::ChooseWeapon()
{
	auto it = this->weaponsData.begin();
	for (size_t i = 0; i < this->weaponsData.size(); i++, it++)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + i)))
		{
			this->weaponIterator = it;
			break;
		}
	}
}

void Weapons::RemoveEmptyWeapon()
{
	if(this->weaponIterator->second.HasBullet()) return;
	this->weaponsData.erase(this->weaponIterator->first);
	this->weaponIterator = this->weaponsData.find("Knife");
}

Weapon& Weapons::GetCurrentWeaponReference()
{
	return this->weaponIterator->second;
}
