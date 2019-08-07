#include "GamePoint.h"



GamePoint::GamePoint(Game::Window & window, Game::Position const & pos, AnimationPack const & animations)
	:Box(window, "check_point", GameObjectParameters(pos.GetPhysicsPos().x, pos.GetPhysicsPos().y, 0.f, 0.f, 0.f, Game::BodyType::Static), animations)
{
	_body->GetFixtureList()->SetSensor(true);
}

