#pragma once
#include "Box.h"
#include <iostream>

class Platform
	: public Box
{
public:
	Platform(Game::Window & window, Game::Position const & pos, AnimationPack const & animations,
			float x_velocity, float y_velocity, float loop_time);
	bool virtual update(Game::Window & window);
private:
	sf::Time _timer;
	b2Vec2 _velocity;
	float _time_to_change_dir;
};

