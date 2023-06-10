#include "ContinuousShootingAnimation.h"

ContinuousShootingAnimation::ContinuousShootingAnimation(sf::Texture& texture)
	: ShootingAnimation(texture)
{
}

void ContinuousShootingAnimation::Shoot()
{
	if (this->shootActivity)
	{
		if (this->shootState == ShootState::DEFAULT) {
			this->animation.Animate(0, 1);
			if (this->animation.GetCurrentFrameIterator() == 1) this->shootState = ShootState::START;
		}
		else
		{
			this->animation.Animate(1, 4);
			if(this->animation.GetCurrentFrameIterator() == 2) this->shootState = ShootState::SHOOT;
			else this->shootState = ShootState::END;
		}
	}
	else if(this->animation.GetCurrentFrameIterator() == 1)
	{
		this->animation.Animate(0, 0);
		this->shootState = ShootState::DEFAULT;
	}
	else if(this->animation.GetCurrentFrameIterator() > 1)
	{
		this->animation.Animate(0, 4);
		if(this->animation.GetCurrentFrameIterator() == 4) this->shootState = ShootState::DEFAULT;
	}
	this->sprite.setTextureRect(this->animation.GetAnimationFrame());
}
