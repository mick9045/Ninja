#include "EndGameObject.h"


EndGameObject::EndGameObject(Game::Window & window, Game::Position const & pos, AnimationPack const & coin_animations)
	:Box(window, "end", GameObjectParameters(pos.GetPixelPos().x, pos.GetPixelPos().y, 0, 0, 0, Game::BodyType::Static), coin_animations)
{
	_body->GetFixtureList()->SetSensor(true);
}
