#include "EnemyObject.h"



EnemyObject::EnemyObject(Game::Window & window, Game::Position const & pos, AnimationPack const & animations, float x_velocity, float y_velocity, float loop_time, bool sensor)
	:Platform(window, pos, animations, x_velocity, y_velocity, loop_time)
{
	_name = "enemy";
	_body->SetBullet(true);
	_body->GetFixtureList()->SetSensor(sensor);
}

