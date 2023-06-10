#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include <memory>
#include "../GameState/GameState.h"
#include "../GameData/GameData.h"

class GameState;

class GameLogic
{
public:
	GameLogic(std::shared_ptr<GameData> gameData);
	void ChangeGameState(std::unique_ptr<GameState> gameState);
	void Update();
	void Draw();
private:
	std::unique_ptr<GameState> gameState;
	std::shared_ptr<GameData> gameData;
};

#endif