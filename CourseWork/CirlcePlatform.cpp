#include "CirclePlatform.h"




CirclePlatform::CirclePlatform(Game::Window & window,
							   Game::Position const & pos,
							   CircleAnimationPack const & animations,
							   float x_velocity,
							   float y_velocity,
							   float loop_time)
	:Circle(window,
			"platform",
			GameObjectParameters(
				pos.GetPixelPos().x,
				pos.GetPixelPos().y,
				1.f, 0.09f, 0.01f,
				Game::BodyType::Kinematic
			),
			animations)
{
	_timer = window.GetTime();
	_time_to_change_dir = loop_time;
	_velocity = b2Vec2(x_velocity, y_velocity);
	_body->SetLinearVelocity(_velocity);
	_velocity.x *= -1;
	_velocity.y *= -1;
}

bool CirclePlatform::update(Game::Window & window)
{
	if (window.GetTime().asSeconds() - _timer.asSeconds() > _time_to_change_dir)
	{
		_timer = window.GetTime();
		_body->SetLinearVelocity(b2Vec2(0, 0));
		_body->SetLinearVelocity(_velocity);
		_velocity.x *= -1;
		_velocity.y *= -1;
	}
	draw(window, false);
	return true;
}
