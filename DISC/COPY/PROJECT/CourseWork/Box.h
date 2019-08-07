#pragma once
#include "BaseGameObject.h"

class Box :
	public BaseGameObject
{
public:
	Box(Game::Window & window, std::string name, GameObjectParameters const & parameters, AnimationPack const & animations);
};

