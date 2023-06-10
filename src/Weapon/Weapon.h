#ifndef WEAPON_H_
#define WEAPON_H_
#include "../ShootingAnimation/ShootingAnimation.h"
#include <memory>

class Weapon
{
public:
	Weapon() = default;
	Weapon(ShootingAnimation* shootingAnimation, int damage, int bulletNumber = -1);
	void PressShoot();
	void Draw(sf::RenderWindow& window);
	void AddBullet(int bullets);
	bool HasBullet() const;
	int GetDamage() const;
	void Shoot();
	bool isShooting() const;
private:
	std::unique_ptr<ShootingAnimation> shootingAnimation;
	const int damage = 0;
	int bulletNumber;
	bool bulletIsEndless;
	sf::Clock shootingClock;
};
#endif