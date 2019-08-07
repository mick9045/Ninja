#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Settings.h"



namespace Game
{
	enum class CoordType
	{
		Pixel, Physics
	};

	enum class BodyType
	{
		Static, Dynamic, Kinematic
	};

	class Vec
	{
	public:
		Vec();
		Vec(CoordType coord_type, float x_, float y_);
		Vec(sf::Vector2f vector);
		Vec(b2Vec2 vector);
		void Set(CoordType pos_type, float x_, float y_);
		sf::Vector2f GetPixelPos() const;
		b2Vec2 GetPhysicsPos() const;
	protected:
		float _x;
		float _y;
	};

	class Position
		:public Vec
	{
	public:
		Position();
		Position(CoordType coord_type, float x_, float y_);
		Position(sf::Vector2f vector);
		Position(b2Vec2 vector);
	public:
		static float DegreesToRadians(float degrees);
		static float RadiansToDegress(float radians);
	};

	class Size
		: public Vec
	{
	public:
		Size(CoordType coord_type, float x_, float y_);
		float GetX();
		float GetY();
		Size();
		Size(float x_, float y_);
	};


}
