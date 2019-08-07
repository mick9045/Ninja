#include "Platform.h"



Platform::Platform(Game::Window & window,
				   Game::Position const & pos,
				   AnimationPack const & animations,
				   float x_velocity,
				   float y_velocity,
				   float loop_time)
	:Box(window,
		 "platform",
		 GameObjectParameters(
			 pos.GetPixelPos().x,
			 pos.GetPixelPos().y,
			 1.f, 1.f, 0.00f,
			 Game::BodyType::Kinematic
		 ),
		animations)
{
	_body->SetBullet(true);
	_timer = window.GetTime();
	_time_to_change_dir = loop_time;
	_velocity = b2Vec2(x_velocity, y_velocity);
	_body->SetLinearVelocity(_velocity);
	_velocity.x *= -1;
	_velocity.y *= -1;
}

bool Platform::update(Game::Window & window)
{
	if (window.GetTime().asSeconds() - _timer.asSeconds() > _time_to_change_dir)
	{
		_timer = window.GetTime();
		//_body->SetLinearVelocity(b2Vec2(0, 0));
		_body->SetLinearVelocity(_velocity);
		_velocity.x *= -1;
		_velocity.y *= -1;
	}
	draw(window, false);
	return true;
}

