#ifndef GAMESTATE_H_
#define GAMESTATE_H_
#include "../GameLogic/GameLogic.h"
#include "../GameData/GameData.h"
class GameLogic;

class GameState
{
public:
	GameState(GameLogic& gameLogic, std::shared_ptr<GameData> gameData);
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	GameLogic& gameLogic;
	std::shared_ptr<GameData> gameData;
};

#endif