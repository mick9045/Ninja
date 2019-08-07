#pragma once
#include "Box.h"


class Heart :
	public Box
{
public:
	Heart(Game::Window & window, Game::Position const & pos, AnimationPack const & coin_animations, bool static_ = true);
	virtual bool update(Game::Window & window);
private:
	bool _destruct;
};

