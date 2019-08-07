#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <memory>
#include "Settings.h"
#include "Adaption.h"
#include "Animation.h"
#include "GameWindow.h"

struct BoxParametres
{
	BoxParametres(float pos_px_x_, float pos_px_y_, float dencity_, float firction_, float restitution_, game::BodyType body_type);
	game::Position initial_pos;
	float dencity;
	float friction;
	float restitution;
	game::BodyType type;
};

class Box_d
{
public:
	Box_d(b2World & world, std::string name, AnimationPack const & animation, BoxParametres const & BoxParameteres);
	void update(game::Window & window);
	void Destroy();
	~Box_d();
private:
	b2Body * _body;
	b2ContactFilter filter;
	
	
	AnimationPack _animation;
	game::Position _pos;
	
};


