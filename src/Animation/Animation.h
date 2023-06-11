#ifndef ANIMATION_H_
#define ANIMATION_H_
#include "SFML/Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation(bool isVertical, size_t frameNumber, float time = 0.06f);
	void Animate(size_t start, size_t end);
	void Restart();
	const sf::IntRect& GetAnimationFrame();
	size_t GetCurrentFrameIterator();
	bool AnimationFrameChanged();
private:
	std::vector<sf::IntRect> textureCoordinates;
	bool animationFrameChanged;
	size_t currentFrameIterator;
	size_t nextFrameIterator;
	const float time;
	sf::Clock animationClock;
};
#endif