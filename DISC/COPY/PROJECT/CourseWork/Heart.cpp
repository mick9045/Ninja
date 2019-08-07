#include "Heart.h"



Heart::Heart(Game::Window & window, Game::Position const & pos, AnimationPack const & heart_animations, bool static_)
	:Box(window, "heart", GameObjectParameters(pos.GetPixelPos().x, pos.GetPixelPos().y, 1.f, 0.09f, 0.1f, static_ ? Game::BodyType::Static : Game::BodyType::Dynamic), heart_animations)
{
	if (static_ == true)
		_body->GetFixtureList()->SetSensor(true);
	_destruct = false;
}

bool Heart::update(Game::Window & window)
{
	if (_destruct == true)
		return false;
	for (b2ContactEdge * contact = _body->GetContactList(); contact != nullptr; contact = contact->next)
	{
		std::string object_a = static_cast<BaseGameObject *>(contact->contact->GetFixtureA()->GetBody()->GetUserData())->GetName();
		std::string object_b = static_cast<BaseGameObject *>(contact->contact->GetFixtureB()->GetBody()->GetUserData())->GetName();
		if (object_a == "player")
			_destruct = true;
	}
	draw(window, false);
	return true;
}
