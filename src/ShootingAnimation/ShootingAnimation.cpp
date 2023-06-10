#include "ShootingAnimation.h"
#include "../Constants/game_settings.h"
#include <iostream>

ShootingAnimation::ShootingAnimation(sf::Texture& texture)
	: sprite(texture), animation(false, 5), shootState(ShootState::DEFAULT), shootActivity(false)
{
	this->sprite.setTextureRect(this->animation.GetAnimationFrame());
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.setScale(3.f, 3.f);
	this->sprite.setPosition(static_cast<float>(window_width) / 2.f, static_cast<float>(window_height) - this->sprite.getGlobalBounds().height / 2.f);
}

void ShootingAnimation::SetShootActivity(bool shootActivity)
{
	this->shootActivity = shootActivity;
}

bool ShootingAnimation::ShootHappening()
{
	return this->shootState == ShootState::SHOOT;
}

void ShootingAnimation::Draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}
