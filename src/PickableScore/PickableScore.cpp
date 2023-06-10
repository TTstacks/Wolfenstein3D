#include "PickableScore.h"

PickableScore::PickableScore(int score)
    : score(score)
{

}

void PickableScore::Update(Player& player, bool& renderable)
{
    player.score += this->score;
    renderable = true;
}