#ifndef SHOOTINGANIMATION_H_
#define SHOOTINGANIMATION_H_
#include "../Animation/Animation.h"
#include "SFML/Graphics.hpp"

class ShootingAnimation
{
public:
	ShootingAnimation(sf::Texture& texture);
	virtual void Shoot() = 0;
	void SetShootActivity(bool shootActivity);
	bool ShootHappening();
	void Draw(sf::RenderWindow& window);
protected:
	sf::Sprite sprite;
	sf::Clock shootingClock;
	Animation animation;
	bool shootActivity;
};
#endif