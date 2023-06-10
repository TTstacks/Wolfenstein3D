#include "PlayingGameState.h"
#include "../Constants/game_settings.h"

PlayingGameState::PlayingGameState(GameLogic& gameLogic, std::shared_ptr<GameData> gameData)
	: GameState(gameLogic, gameData), gameData(gameData), player(gameData, sf::Vector2f(1.f, 1.f), 0.f, 0.009f, 100), walls(gameData), objects(gameData, player, enemies), yellowWarningColor(255, 255, 0, 200), renderYellowWarning(false), canDrawYellowWarning(false)
{
	this->player.weapons.AddWeapon("Pistol", 10);
	this->yellowWarning.setSize(sf::Vector2f(window_width, window_height));
	this->yellowWarning.setFillColor(this->yellowWarningColor);
}

void PlayingGameState::Update()
{
	this->player.Move();
	this->player.Rotate();
	this->player.weapons.RemoveEmptyWeapon();
	this->player.weapons.ChooseWeapon();
	this->player.weapons.GetCurrentWeaponReference().PressShoot();
	this->player.weapons.GetCurrentWeaponReference().Shoot();
	this->walls.Update(this->player.GetAngle(), this->player.GetPosition(), this->renderableObjects);
	this->enemies.Update();
	this->objects.Update(this->player, this->renderableObjects, this->renderYellowWarning);
}

void PlayingGameState::Draw()
{
	this->renderableObjects.Draw(this->gameData);
	this->player.weapons.GetCurrentWeaponReference().Draw(this->gameData->window);
	this->DrawYellowWarning();
}

void PlayingGameState::DrawYellowWarning()
{
	if(this->renderYellowWarning)
	{
		this->canDrawYellowWarning = true;
		this->yellowWarningColor = sf::Color(255, 255, 0, 200);
		this->renderYellowWarning = false;
	}
	if(this->canDrawYellowWarning)
	{
		this->gameData->window.draw(this->yellowWarning);
		if(this->yellowWarningClock.getElapsedTime().asSeconds() > 0.06f)
		{
			this->yellowWarningColor.a -= 20;
			this->yellowWarningClock.restart();
		}
		if(!this->yellowWarningColor.a)
		{
			this->canDrawYellowWarning = false;
		}
		this->yellowWarning.setFillColor(this->yellowWarningColor);
	}
	
}
