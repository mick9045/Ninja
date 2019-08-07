#pragma once
#include "Box.h"


class GamePoint :
	public Box
{
public:
	GamePoint(Game::Window & window, Game::Position const & position, AnimationPack const & animation);
};

