#include "BaseGameObject.h"


BaseGameObject::BaseGameObject(AnimationPack const & animation_pack)
	: _animation_pack(animation_pack)
{
	_body = nullptr;
}
/*
BaseGameObject::BaseGameObject(b2World & world, std::string name, AnimationPack const & animation, GameObjectParameters const & box_parameters, b2Shape const & shape)
	: BaseGameObject(animation)
{
	Initialize(world, name, box_parameters, shape);
}
*/
BaseGameObject::BaseGameObject(Game::Window & _window,
							   std::string name,
							   AnimationPack const & animation,
							   GameObjectParameters const & BoxParameteres,
							   b2Shape const & shape)
	: BaseGameObject(animation)
{
	Initialize(
		_window,
		name,
		BoxParameteres,
		shape
	);
}

BaseGameObject::BaseGameObject(BaseGameObject const && game_obj)
	: _animation_pack(game_obj._animation_pack)
{
	_name = game_obj._name;
	_body = game_obj._body;
	const_cast<BaseGameObject &> (game_obj)._body = nullptr;
	_body->SetUserData(this);
}


bool BaseGameObject::Initialized()
{
	return _body ? true : false;
}

bool BaseGameObject::update(Game::Window & window)
{
	draw(window);	
	return true;
}

Game::Position BaseGameObject::GetPosition() const
{
	return Game::Position(
		Game::CoordType::Physics,
		_body->GetPosition().x,
		_body->GetPosition().y
	);
}

void BaseGameObject::move(Game::Position const & position, float angle)
{
	_body->SetTransform(
		position.GetPhysicsPos(),
		Game::Position::DegreesToRadians(angle)
	);
}

const std::string & BaseGameObject::GetName()
{
	return _name;
}

BaseGameObject::~BaseGameObject()
{
	if (_body != nullptr)
		_body->GetWorld()->DestroyBody(_body);
	_body = nullptr;
}


//void BaseGameObject::Initialize(b2World & world, std::string const & name ,GameObjectParameters const & parameters, b2Shape const & shape, float angle)
//{
//	if (_body)
//		this->~BaseGameObject();
//	b2BodyDef body_def;
//	body_def.position = parameters.initial_pos.GetPhysicsPos();
//	switch (parameters.type)
//	{
//	case Game::BodyType::Static:
//		body_def.type = b2_staticBody;
//		break;
//	case Game::BodyType::Dynamic:
//		body_def.type = b2_dynamicBody;
//		break;
//	default:
//		body_def.type = b2_kinematicBody;
//		break;
//	}
//	_name = name;
//	body_def.angle = Game::Position::DegreesToRadians(angle);
//	b2FixtureDef fixture_def;
//	fixture_def.density = parameters.dencity;
//	fixture_def.friction = parameters.friction;
//	fixture_def.restitution = parameters.restitution;
//	fixture_def.shape = &shape;
//	_body = world.CreateBody(&body_def);
//	_body->CreateFixture(&fixture_def);
//	_body->SetUserData(this);
//}


void BaseGameObject::Initialize(Game::Window & window,
								std::string const & name,
								GameObjectParameters const & parameters,
								b2Shape const & shape,
								float angle) // initialize Game object
{
	if (_body)
		this->~BaseGameObject();
	b2BodyDef body_def;
	body_def.position.x = 
		parameters.initial_pos.GetPhysicsPos().x;
	body_def.position.y =
		parameters.initial_pos.GetPhysicsPos().y;
	switch (parameters.type) // Set Body Type
	{
	case Game::BodyType::Static:  // object doesn't react on collisions and can't move
		body_def.type = b2_staticBody;
		break;
	case Game::BodyType::Dynamic: // obect react on collisions and can move
		body_def.type = b2_dynamicBody;
		break;
	case Game::BodyType::Kinematic :
		body_def.type = b2_kinematicBody; // object doesn't react on collisions and can move
		break;
	}
	_name = name;
	body_def.angle = Game::Position::DegreesToRadians(angle);
	body_def.fixedRotation = false;
	b2FixtureDef fixture_def;
	fixture_def.density = parameters.dencity; 
	fixture_def.friction = parameters.friction;
	fixture_def.restitution = parameters.restitution;
	fixture_def.shape = &shape; // setting the shape of fixture
	_body = window.GetWorld().CreateBody(&body_def); // adding body to physics world
	_body->CreateFixture(&fixture_def); // ading fixture to body
	_body->SetUserData(this);
}

void BaseGameObject::draw(Game::Window & window, bool flip)
{
	Game::Position * position = new Game::Position(
		Game::CoordType::Physics,
		_body->GetPosition().x,
		_body->GetPosition().y
	);

	float angle = Game::Position::RadiansToDegress(_body->GetAngle()) / 2;
	
	_animation_pack.Draw(
		window, *position,
		angle, flip
	);
	delete position;
}

GameObjectParameters::GameObjectParameters(float pos_px_x_,
										   float pos_px_y_,
										   float dencity_,
										   float friction_,
										   float restitution_,
										   Game::BodyType body_type)
{
	initial_pos.Set(Game::CoordType::Pixel, pos_px_x_, pos_px_y_);
	dencity = dencity_;
	friction = friction_;
	restitution = restitution_;
	type = body_type;
}
