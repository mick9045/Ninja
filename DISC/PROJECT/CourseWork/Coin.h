#pragma once
#include "Circle.h"


class Coin :
	public Circle
{
public:
	Coin(Game::Window & window, Game::Position const & pos, CircleAnimationPack const & coin_animations, bool static_ = true);
	virtual bool update(Game::Window & window);
private:
	bool _destruct;
};

