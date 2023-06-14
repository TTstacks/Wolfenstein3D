#include "ContinuousShootingAnimation.h"

ContinuousShootingAnimation::ContinuousShootingAnimation(sf::Texture& texture)
	: ShootingAnimation(texture)
{
}

void ContinuousShootingAnimation::Shoot()
{
	if(this->shootActivity)
	{
		this->animation.Animate(1, 4);
	}
	else if(this->animation.GetCurrentFrameIterator() == 1) this->animation.Animate(0, 0);
	else if(this->animation.GetCurrentFrameIterator() > 1)
	{
		if(this->animation.GetCurrentFrameIterator() == 4) this->animation.Animate(0, 0);
		else this->animation.Animate(this->animation.GetCurrentFrameIterator(), 4);
	}
	this->sprite.setTextureRect(this->animation.GetAnimationFrame());
}
