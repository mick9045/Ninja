#pragma once
#include "Platform.h"

class EnemyObject :
	public Platform
{
public:
	EnemyObject(Game::Window & window, Game::Position const & pos, AnimationPack const & animations, float x_velocity, float y_velocity, float loop_time, bool sensor);
};

