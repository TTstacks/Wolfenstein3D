#ifndef ENDINGGAMESTATE_H_
#define ENDINGGAMESTATE_H_
#include "../GameState/GameState.h"

class EndingGameState : public GameState
{
public:
	EndingGameState(GameLogic& gameLogic, std::shared_ptr<GameData> gameData);
	void Update() final;
	void Draw() final;
private:
};
#endif