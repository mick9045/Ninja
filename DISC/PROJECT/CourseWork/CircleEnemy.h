#pragma once
#include "CirclePlatform.h"


class CircleEnemy :
	public CirclePlatform
{
public:
	CircleEnemy(Game::Window & window, Game::Position const & pos, CircleAnimationPack const & animations, float x_velocity, float y_velocity, float loop_time, bool sensor, int linearVelocity = 0);
};

