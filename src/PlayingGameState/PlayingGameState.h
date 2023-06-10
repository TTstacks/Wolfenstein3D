#ifndef PLAYINGGAMESTATE_H_
#define PLAYINGGAMESTATE_H_
#include "../GameState/GameState.h"
#include "../Player/Player.h"
#include "../RenderableObjects/RenderableObjects.h"
#include "../Walls/Walls.h"
#include "../Objects/Objects.h"
#include "../Enemies/Enemies.h"

class PlayingGameState : public GameState
{
public:
	PlayingGameState(GameLogic& gameLogic, std::shared_ptr<GameData> gameData);
	void Update() final;
	void Draw() final;
private:
	void DrawYellowWarning();
private:
	std::shared_ptr<GameData> gameData;
	Player player;
	RenderableObjects renderableObjects;
	Walls walls;
	Enemies enemies;
	Objects objects;
	bool renderYellowWarning;
	bool canDrawYellowWarning;
	sf::RectangleShape yellowWarning;
	sf::Color yellowWarningColor;
	sf::Clock yellowWarningClock;
};
#endif