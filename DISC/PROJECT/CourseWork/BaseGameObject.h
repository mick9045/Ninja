#pragma once
#include "Exceptions.h"
#include "Coord.h"
#include "Animation.h"
#include "GameWindow.h"

struct GameObjectParameters
{
	GameObjectParameters(float pos_px_x_, float pos_px_y_, float density_, float friction_, float restitution_, Game::BodyType body_type);
	Game::Position initial_pos;
	float dencity;
	float friction;
	float restitution;
	Game::BodyType type;
};

class BaseGameObject // base object
{
public:
	BaseGameObject(AnimationPack const & animation_pack);
	BaseGameObject(Game::Window & window, std::string name, AnimationPack const & animation, GameObjectParameters const & BoxParameteres, b2Shape const & shape);
	BaseGameObject(BaseGameObject const && game_obj);
	BaseGameObject(BaseGameObject const & game_obj) = delete;
	BaseGameObject & operator=(BaseGameObject const & base_game_object) = delete;
	bool Initialized();
	virtual bool update(Game::Window & window); // update Game object 
	Game::Position GetPosition() const;
	void move(Game::Position const &, float angle = 0);
	const std::string & GetName();

	virtual ~BaseGameObject() = 0;

protected:
	//data
	b2Body * _body;
	AnimationPack _animation_pack;
	std::string _name;
	//method(s)
	void Initialize(Game::Window & window, std::string const & name, GameObjectParameters const & parameters, b2Shape const & shape, float angle = 0);
	void draw(Game::Window & window, bool flip = false);
};

