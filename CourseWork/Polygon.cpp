#include "Polygon.h"


Polygon::Polygon(Game::Window & world, std::string name, GameObjectParameters const & parameters, AnimationPack const & animations, std::vector<Game::Position> const & points_pos)
	: BaseGameObject(animations)
{
	if (points_pos.size() > b2_maxPolygonVertices)
		throw exc::InvalidGameObjectParameters("more Polygons than allowed");
	b2Vec2 * vertices = new b2Vec2[points_pos.size()];
	for (WORD i = 0; i < points_pos.size(); i++)
	{
		if (abs(points_pos[i].GetPixelPos().x) > animations.GetFrameWidth() / 2 || abs(points_pos[i].GetPixelPos().y) > animations.GetFrameHeight() / 2)
		{
			delete[] vertices;
			std::string exception = "Invalid polygon point number ";
			exception += i + '0';
			throw exc::InvalidGameObjectParameters("Invalid polygon point");
		}
		else
		{
			vertices[i].x = points_pos[i].GetPhysicsPos().x;
			vertices[i].y = points_pos[i].GetPhysicsPos().y;
		}
	}
	b2PolygonShape shape;
	shape.Set(vertices, points_pos.size());
	Initialize(world, name, parameters, shape);
	delete[] vertices;
}
