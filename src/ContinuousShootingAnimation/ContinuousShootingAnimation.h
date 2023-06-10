#ifndef CONTINUOUSSHOOTINGANIMATION_H_
#define CONTINUOUSSHOOTINGANIMATION_H_
#include "../ShootingAnimation/ShootingAnimation.h"
class ContinuousShootingAnimation : public ShootingAnimation
{
public:
	ContinuousShootingAnimation(sf::Texture& texture);
	void Shoot() final;
};

#endif