#pragma once
#include "Circle.h"


class CirclePlatform :
	public Circle
{
public:
	CirclePlatform(Game::Window & window, Game::Position const & pos, CircleAnimationPack const & animations, float x_velocity, float y_velocity, float loop_time);
	bool virtual update(Game::Window & windoow);
private:
	sf::Time _timer;
	b2Vec2 _velocity;
	float _time_to_change_dir;
};

