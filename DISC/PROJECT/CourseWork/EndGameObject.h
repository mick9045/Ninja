#pragma once
#include "Box.h"

class EndGameObject
	: public Box
{
public:
	EndGameObject(Game::Window & window, Game::Position const & pos, AnimationPack const & coin_animations);
};

