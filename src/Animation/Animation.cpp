#include "Animation.h"
#include "../Constants/texture_settings.h"

Animation::Animation(bool isVertical, const size_t frameNumber, float time)
	: nextFrameIterator(0), currentFrameIterator(0), animationFrameChanged(false), time(time)
{
	this->textureCoordinates.resize(frameNumber);
	for (size_t i = 0; i < frameNumber; i++)
	{
		this->textureCoordinates[i].top = 0;
		this->textureCoordinates[i].left = static_cast<int>(i) * texture_size;
		if (isVertical) std::swap(this->textureCoordinates[i].top, this->textureCoordinates[i].left);
		this->textureCoordinates[i].height = texture_size;
		this->textureCoordinates[i].width = texture_size;
	}
}

void Animation::Animate(size_t start, size_t end)
{
	this->animationFrameChanged = false;
	if(this->animationClock.getElapsedTime().asSeconds() > time)
	{
		this->currentFrameIterator = this->nextFrameIterator;
		this->nextFrameIterator = this->currentFrameIterator + 1;
		if (this->currentFrameIterator < start || this->currentFrameIterator > end) 
		{
			this->currentFrameIterator = start;
			this->nextFrameIterator = start + 1;
		}
		this->animationClock.restart();
		this->animationFrameChanged = true;
	}
}

void Animation::Restart()
{
	this->currentFrameIterator = this->nextFrameIterator = 0;
}

const sf::IntRect& Animation::GetAnimationFrame()
{
	return this->textureCoordinates[this->currentFrameIterator];
}

size_t Animation::GetCurrentFrameIterator()
{
	return this->currentFrameIterator;
}

bool Animation::AnimationFrameChanged()
{
	return this->animationFrameChanged;
}
