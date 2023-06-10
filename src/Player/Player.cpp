#include "Player.h"
#include "../WorldMap/WorldMap.h"
#include "../Constants/ray_cast_settings.h"
#include "../Constants/game_settings.h"
#include <iostream>
#include <cmath>

Player::Player(std::shared_ptr<GameData> gameData, const sf::Vector2f& position, float angle, float speed, int health)
	: gameData(gameData), weapons(gameData), position(position), angle(angle), speed(speed), health(health), score(0)
{
	
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
