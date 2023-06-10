#ifndef GAME_H_
#define GAME_H_
#include "../GameLogic/GameLogic.h"
#include "../GameData/GameData.h"
#include <memory>

class Game
{
public:
	Game();
private:
	void Update();
	void HandleEvent();
	void Draw();
private:
	std::shared_ptr<GameData> gameData;
	std::unique_ptr<GameLogic> gameLogic;
};
#endif