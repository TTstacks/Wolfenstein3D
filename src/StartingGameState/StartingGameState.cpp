#include "StartingGameState.h"

StartingGameState::StartingGameState(GameLogic& gameLogic, std::shared_ptr<GameData> gameData)
	: GameState(gameLogic, gameData)
{
}

void StartingGameState::Update()
{
}

void StartingGameState::Draw()
{
}
