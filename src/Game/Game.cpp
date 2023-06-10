#include "Game.h"
#include "../Constants/game_settings.h"

Game::Game()
	: gameData(std::make_shared<GameData>())
{
	this->gameData->window.setFramerateLimit(60);
	this->gameData->resourceManager.AddTexture("images/Weapons/Chaingun.png", "Chaingun");
	this->gameData->resourceManager.AddTexture("images/Weapons/Knife.png", "Knife");
	this->gameData->resourceManager.AddTexture("images/Weapons/MachineGun.png", "MachineGun");
	this->gameData->resourceManager.AddTexture("images/Weapons/Pistol.png", "Pistol");
	this->gameData->resourceManager.AddTexture("images/Walls/Wall1.png", "Wall1");
	this->gameData->resourceManager.AddTexture("images/Enemies/SS/Angles.png", "SS/Angles");
	this->gameData->resourceManager.AddTexture("images/Enemies/SS/Shooting.png","SS/Shooting");
	this->gameData->resourceManager.AddTexture("images/Enemies/SS/Damaged.png", "SS/Damaged");
	this->gameData->resourceManager.AddTexture("images/Enemies/SS/Dying.png","SS/Dying");
	this->gameData->resourceManager.AddTexture("images/Objects/Statue/Statue.png", "Statue");
	this->gameData->resourceManager.AddTexture("images/Objects/Table/Table.png", "Table");
	this->gameData->resourceManager.AddTexture("images/Objects/Knight/Knight.png", "Knight");
	this->gameData->resourceManager.AddTexture("images/Pickup/Ammo/ChainGun.png", "ChainGun Ammo");
	this->gameData->resourceManager.AddTexture("images/Pickup/Ammo/MachineGun.png", "MachineGun Ammo");
	this->gameData->resourceManager.AddTexture("images/Pickup/Ammo/Magazine.png", "Magazine");
	this->gameData->resourceManager.AddTexture("images/Pickup/Health/Head.png", "Health Head");
	this->gameData->resourceManager.AddTexture("images/Pickup/Health/Medicine.png", "Medicine");
	this->gameData->resourceManager.AddTexture("images/Pickup/Score/Cross.png", "Cross");
	this->gameData->resourceManager.AddTexture("images/Pickup/Score/Crown.png", "Crown");
	this->gameData->resourceManager.AddTexture("images/Pickup/Score/Medal.png", "Medal");
	this->gameData->resourceManager.AddTexture("images/Pickup/Score/Treasure.png", "Treasure");
	this->gameData->resourceManager.AddTexture("images/Player/Head/Head.png", "Head");
	this->gameData->resourceManager.AddTexture("images/Player/Bar/Bar.png", "Bar");
	this->gameData->window.create(sf::VideoMode(window_width, window_height), "Wolfenstein3D");
	this->gameData->window.setMouseCursorVisible(false);
	this->gameLogic = std::make_unique<GameLogic>(this->gameData);
	this->Update();
}

void Game::Update()
{
	while (this->gameData->window.isOpen())
	{
		this->HandleEvent();
		this->gameLogic->Update();
		this->Draw();
	}
}

void Game::HandleEvent()
{
	sf::Event event;
	while (this->gameData->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) this->gameData->window.close();
		else if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Escape) this->gameData->window.close();
	}
}

void Game::Draw()
{
	this->gameData->window.clear();
	this->gameLogic->Draw();
	this->gameData->window.display();
}
