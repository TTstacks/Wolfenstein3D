#ifndef PLAYER_H_
#define PLAYER_H_
#include <memory>
#include "SFML/Graphics.hpp"
#include "../Weapons/Weapons.h"
#include "../GameData/GameData.h"

class Player
{
public:
	Player(std::shared_ptr<GameData> gameData, const sf::Vector2f& position, float angle, float speed, int health);
	const float& GetAngle();
	const sf::Vector2f& GetPosition();
	void Rotate();
	void Move();
	void DrawBar();
	void DrawRedWarning();
public:
	int health;
	int score;
	Weapons weapons;
	bool renderRedWarning;
private:
	std::shared_ptr<GameData> gameData;
	float angle;
	float speed;
	sf::Vector2f position;
	sf::Sprite barSprite;
	sf::Sprite headSprite;
	sf::Text healthText;
	sf::Text ammoText;
	sf::RectangleShape redWarning;
	sf::Color redWarningColor;
	sf::Clock redWarningClock;
	bool canDrawRedWarning;
};
#endif