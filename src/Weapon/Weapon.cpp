#include "Weapon.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Weapon::Weapon(ShootingAnimation* shootingAnimation, int damage, int bulletNumber)
	: shootingAnimation(shootingAnimation), damage(damage), bulletNumber(bulletNumber), bulletIsEndless(bulletNumber == -1)
{

}

void Weapon::PressShoot()
{
	this->shootingAnimation->SetShootActivity(sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

void Weapon::Draw(sf::RenderWindow& window)
{
	this->shootingAnimation->Draw(window);
}

void Weapon::AddBullet(int bullets)
{
	this->bulletNumber += bullets;
}

bool Weapon::HasBullet() const
{
	if(bulletIsEndless) return true;
	return this->bulletNumber > 0;
}

int Weapon::GetDamage() const
{
	return this->damage;
}

void Weapon::Shoot()
{
	this->shootingAnimation->Shoot();
	this->shootingClock.restart();
	if (this->bulletIsEndless) return;
	if(isShooting()) bulletNumber--;
}

bool Weapon::isShooting() const
{
	return this->shootingAnimation->ShootHappening();
}
