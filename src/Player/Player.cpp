#include "Player.h"
#include "../WorldMap/WorldMap.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/game_settings.h"
#include <iostream>
#include <cmath>

Player::Player(std::shared_ptr<GameData> gameData, const sf::Vector2f& position, float angle, float speed, int health)
	: gameData(gameData), weapons(gameData), position(position), angle(angle), speed(speed), health(health), score(0), redWarningColor(sf::Color(255, 0, 0, 100)), renderRedWarning(false), canDrawRedWarning(false)
{
	this->barSprite.setTexture(this->gameData->resourceManager.GetTexture("Bar"));
	this->barSprite.setScale(static_cast<float>(window_width) / this->barSprite.getLocalBounds().width, static_cast<float>(task_bar_height) / this->barSprite.getLocalBounds().height);
	this->barSprite.setPosition(0.f, static_cast<float>(window_height));
	this->headSprite.setTexture(this->gameData->resourceManager.GetTexture("Head"));
	float scaleY = static_cast<float>(task_bar_height) / this->headSprite.getLocalBounds().height - 0.1f;
	this->headSprite.setScale(scaleY, scaleY);
	this->headSprite.setPosition(292.5f, window_height + 9.f);
	this->healthText.setFont(this->gameData->resourceManager.GetFont("FFFFORWA"));
	this->healthText.setPosition(370.f, window_height + 45.f);
	this->healthText.setCharacterSize(25);
	this->ammoText.setFont(this->gameData->resourceManager.GetFont("FFFFORWA"));
	this->ammoText.setPosition(470.f, window_height + 45.f);
	this->redWarning.setSize(sf::Vector2f(window_width, window_height));
	this->redWarning.setFillColor(this->redWarningColor);
}

const float& Player::GetAngle()
{
	return this->angle;
}

const sf::Vector2f& Player::GetPosition()
{
	return this->position;
}

void Player::Rotate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) this->angle -= pi / 180.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->angle += pi / 180.f;
	this->angle += static_cast<float>((sf::Mouse::getPosition(this->gameData->window).x - static_cast<int>(half_window_width))) * 0.01f;
	sf::Mouse::setPosition(sf::Vector2i(half_window_width, half_window_height), this->gameData->window);
	this->angle = std::fmod(this->angle, 2 * pi);
}

void Player::Move()
{
	const float movementX = std::cos(angle) * this->speed;
	const float movementY = std::sin(angle) * this->speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
	{
		const sf::Vector2f newPlayerPosition(this->position.x + movementX, this->position.y + movementY);
		if (!WorldMap::GetElement(static_cast<size_t>(newPlayerPosition.x), static_cast<size_t>(this->position.y))) this->position.x = newPlayerPosition.x;
		if (!WorldMap::GetElement(static_cast<size_t>(this->position.x), static_cast<size_t>(newPlayerPosition.y))) this->position.y = newPlayerPosition.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		const sf::Vector2f newPlayerPosition(this->position.x - movementY, this->position.y + movementX);
		if (!WorldMap::GetElement(static_cast<size_t>(newPlayerPosition.x), static_cast<size_t>(this->position.y))) this->position.x = newPlayerPosition.x;
		if (!WorldMap::GetElement(static_cast<size_t>(this->position.x), static_cast<size_t>(newPlayerPosition.y))) this->position.y = newPlayerPosition.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		const sf::Vector2f newPlayerPosition(this->position.x - movementX, this->position.y - movementY);
		if (!WorldMap::GetElement(static_cast<size_t>(newPlayerPosition.x), static_cast<size_t>(this->position.y))) this->position.x = newPlayerPosition.x;
		if (!WorldMap::GetElement(static_cast<size_t>(this->position.x), static_cast<size_t>(newPlayerPosition.y))) this->position.y = newPlayerPosition.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		const sf::Vector2f newPlayerPosition(this->position.x + movementY, this->position.y - movementX);
		if (!WorldMap::GetElement(static_cast<size_t>(newPlayerPosition.x), static_cast<size_t>(this->position.y))) this->position.x = newPlayerPosition.x;
		if (!WorldMap::GetElement(static_cast<size_t>(this->position.x), static_cast<size_t>(newPlayerPosition.y))) this->position.y = newPlayerPosition.y;
	}
}

void Player::DrawBar()
{
	this->gameData->window.draw(this->barSprite);
	int rectLeft = (7 - (std::max(this->health, 0) / 14)) * 85;
	this->headSprite.setTextureRect(sf::IntRect(rectLeft, 0,  85,  110));
	this->gameData->window.draw(this->headSprite);
	this->healthText.setString(std::to_string(std::max(this->health, 0)) + "%");
	this->gameData->window.draw(this->healthText);
	std::string bulletText = this->weapons.GetCurrentWeaponReference().GetBullet() == -1? "Inf" : std::to_string(this->weapons.GetCurrentWeaponReference().GetBullet()); 
	this->ammoText.setString(bulletText);
	this->gameData->window.draw(this->ammoText);
}

void Player::DrawRedWarning()
{
	if(this->renderRedWarning)
	{
		this->canDrawRedWarning = true;
		this->redWarningColor = sf::Color(255, 0, 0, 100);
		this->renderRedWarning = false;
	}
	if(this->canDrawRedWarning)
	{
		this->gameData->window.draw(this->redWarning);
		if(this->redWarningClock.getElapsedTime().asSeconds() > 0.06f)
		{
			this->redWarningColor.a -= 20;
			this->redWarningClock.restart();
		}
		if(!this->redWarningColor.a)
		{
			this->canDrawRedWarning = false;
		}
		this->redWarning.setFillColor(this->redWarningColor);
	}
}