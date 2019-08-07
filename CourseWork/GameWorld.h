#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <list>
#include <memory>
#include "Settings.h"
#include "GameObjects.h"
#include "GameWindow.h"
#include "Player.h"


class GameWorld
{
public:
	GameWorld(); // default constructor sets the World gravity (0, 9.8)
	GameWorld(std::string title, float X_gravity, float Y_gravity);
	void InstructionsScreen();
	void Launch();
	~GameWorld();

private:
	std::list<BaseGameObject *> _entities;
	void LastScreen();
	void GameClosing();
	void Initialize();
	Game::Window _window;
	Player _player;
	
};


