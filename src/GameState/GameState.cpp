#include "GameState.h"

GameState::GameState(GameLogic& gameLogic, std::shared_ptr<GameData> gameData)
	: gameLogic(gameLogic)
{
}
