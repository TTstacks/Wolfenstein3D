#ifndef CONSTANTSHOOTINGANIMATION_H_
#define CONSTANTSHOOTINGANIMATION_H_
#include "../ShootingAnimation/ShootingAnimation.h"

class ConstantShootingAnimation : public ShootingAnimation
{
public:
	ConstantShootingAnimation(sf::Texture& texture);
	void Shoot() final;
};
#endif