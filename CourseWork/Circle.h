#pragma once
#include "BaseGameObject.h"


class Circle
	: public BaseGameObject
{
public:
	Circle(Game::Window & window, std::string name, GameObjectParameters const & parameters, CircleAnimationPack const & animations);
};

