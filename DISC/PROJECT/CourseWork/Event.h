#pragma once
#include<SFML\Graphics.hpp>

sf::Event ev;

namespace Game
{
	enum EventType
	{
		KeyPressed, Resiezed, RightClick, LeftClick, WheelMoved, Exit
	};

	class Event
	{
	public:
		Event(EventType ev);
		
	private:
		EventType _type;
	};
}
