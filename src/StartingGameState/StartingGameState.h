#ifndef STARTINGGAMESTATE_H_
#define STARTINGGAMESTATE_H_
#include "../GameState/GameState.h"

class StartingGameState : public GameState
{
public:
	StartingGameState(GameLogic& gameLogic, std::shared_ptr<GameData> gameData);
	void Update() final;
	void Draw() final;
private:
};
#endif