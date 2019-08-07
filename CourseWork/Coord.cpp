#include "Coord.h"


Game::Vec::Vec()
{
	_x = _y = 0;
}

Game::Vec::Vec(CoordType pos_type, float x_, float y_)
{
	if (pos_type == CoordType::Pixel)
	{
		_x = x_;
		_y = y_;
	}
	else
	{
		_x = x_ / GameParameters::scaling;
		_y = y_ / GameParameters::scaling;
	}

}

Game::Vec::Vec(sf::Vector2f vector)
{
	_x = vector.x;
	_y = vector.y;
}

Game::Vec::Vec(b2Vec2 vector)
{
	_x = vector.x / GameParameters::scaling;
	_y = vector.y / GameParameters::scaling;
}

void Game::Vec::Set(CoordType pos_type, float x_, float y_)
{
	if (pos_type == CoordType::Physics) {
		_x = x_ / GameParameters::scaling;
		_y = y_ / GameParameters::scaling;
	}
	else {
		_x = x_;
		_y = y_;
	}
}

Game::Position::Position()
	:Vec()
{
}

Game::Position::Position(CoordType coord_type, float x_, float y_)
	:Vec(coord_type, x_, y_)
{
}

Game::Position::Position(sf::Vector2f vector)
	:Vec(vector)
{
}

Game::Position::Position(b2Vec2 vector)
	:Vec(vector)
{
}

float Game::Position::DegreesToRadians(float degrees)
{
	return degrees * (b2_pi / 180);
}

float Game::Position::RadiansToDegress(float radians)
{
	return radians * (180 / b2_pi);
}

sf::Vector2f Game::Vec::GetPixelPos() const
{
	return sf::Vector2f(_x, _y);
}

b2Vec2 Game::Vec::GetPhysicsPos() const
{
	return b2Vec2(_x * GameParameters::scaling, _y * GameParameters::scaling);
}

Game::Size::Size(CoordType coord_type, float x_, float y_)
	:Vec(coord_type, x_, y_)
{
}

float Game::Size::GetX()
{
	return _x;
}

float Game::Size::GetY()
{
	return _y;
}

Game::Size::Size()
	: Vec()
{
}

Game::Size::Size(float x_, float y_)
	: Vec(CoordType::Pixel, x_, y_)
{
}
