#include "ConstantShootingAnimation.h"

ConstantShootingAnimation::ConstantShootingAnimation(sf::Texture& texture)
	: ShootingAnimation(texture)
{
}

void ConstantShootingAnimation::Shoot()
{
	if(this->shootActivity)
	{
		if(this->animation.GetCurrentFrameIterator() <= 1) this->animation.Animate(1, 2);
		else this->animation.Animate(2, 3);
	}
	else if(this->animation.GetCurrentFrameIterator() == 1) this->animation.Animate(0, 0);
	else if(this->animation.GetCurrentFrameIterator() > 1) 
	{
		if(this->animation.GetCurrentFrameIterator() == 4) this->animation.Animate(0, 0);
		else this->animation.Animate(this->animation.GetCurrentFrameIterator(), 4);
	}
	this->sprite.setTextureRect(this->animation.GetAnimationFrame());
}
