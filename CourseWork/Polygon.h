#pragma once
#include "BaseGameObject.h"

class Polygon
	: public BaseGameObject
{
public:
	//Polygon(b2World & World, std::string name, GameObjectParameters const & parameters, AnimationPack const & animations, std::vector<Game::Position> const & points_pos); // maximum points count is 8
	Polygon(Game::Window & _world, std::string name, GameObjectParameters const & parameters, AnimationPack const & animations, std::vector<Game::Position> const & points_pos); // maximum points count is 8


};

