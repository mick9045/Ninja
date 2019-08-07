#include "Circle.h"


Circle::Circle(Game::Window & world, std::string name, GameObjectParameters const & parameters, CircleAnimationPack const & animations)
	: BaseGameObject(animations)
{
	b2CircleShape shape;
	shape.m_radius = static_cast<float32> (animations.GetTextureRadius()) * GameParameters::scaling;
	Initialize(world, name, parameters, shape);
}


