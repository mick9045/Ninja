#include "CircleEnemy.h"



CircleEnemy::CircleEnemy(Game::Window & window, Game::Position const & pos, CircleAnimationPack const & animations, float x_velocity, float y_velocity, float loop_time, bool sensor, int linearVelocity)
	:CirclePlatform(window, pos, animations, x_velocity, y_velocity, loop_time)
{
	_name = "enemy";
	_body->SetBullet(true);
	_body->SetAngularVelocity(linearVelocity);
	_body->GetFixtureList()->SetSensor(sensor);
}
