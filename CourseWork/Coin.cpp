#include "Coin.h"



Coin::Coin(Game::Window & window, Game::Position const & pos, CircleAnimationPack const & coin_animations, bool static_)
	:Circle(window, "coin", GameObjectParameters(pos.GetPixelPos().x, pos.GetPixelPos().y, 1.f, 0.09f, 0.1f, static_ ? Game::BodyType::Static : Game::BodyType::Dynamic), coin_animations)
{
	if (static_)
		_body->GetFixtureList()->SetSensor(true);
	_destruct = false;
}

bool Coin::update(Game::Window & window)
{
	if (_destruct == true)
		return false;
	for (b2ContactEdge * contact = _body->GetContactList(); contact != nullptr; contact = contact->next)
	{
		std::string object_a = static_cast<BaseGameObject *>(contact->contact->GetFixtureA()->GetBody()->GetUserData())->GetName();
		std::string object_b = static_cast<BaseGameObject *>(contact->contact->GetFixtureB()->GetBody()->GetUserData())->GetName();
		if (object_a == "player") {
			_destruct = true;
		}
	}
	draw(window, false);
	return true;
}
