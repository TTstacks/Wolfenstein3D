#include "GameLogic.h"
#include "../PlayingGameState/PlayingGameState.h"

GameLogic::GameLogic(std::shared_ptr<GameData> gameData)
	: gameData(gameData), gameState(new PlayingGameState(*this, gameData))
{
}

void GameLogic::ChangeGameState(std::unique_ptr<GameState> gameState)
{
	this->gameState = std::move(gameState);
}

void GameLogic::Update()
{
	this->gameState->Update();
}

void GameLogic::Draw()
{
	this->gameState->Draw();
}
