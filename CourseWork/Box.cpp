#include "Box.h"



Box::Box(Game::Window & window, std::string name, GameObjectParameters const & parameters, AnimationPack const & animations)
	: BaseGameObject(animations)
{
	b2PolygonShape shape;
	shape.SetAsBox((static_cast<float32> (animations.GetFrameWidth()) / 2) * GameParameters::scaling, (static_cast<float32> (animations.GetFrameHeight()) / 2) * GameParameters::scaling);
	Initialize(window, name, parameters, shape);
}