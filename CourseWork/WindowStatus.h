#pragma once
#include "SFML\Graphics.hpp"

namespace Game
{
	enum EventType
	{
		Mouse,  
	};

	class WindowStatus
	{
	public:
		WindowStatus(bool status);
		bool isOkey();
	private:
		bool _status;
		bool _resiezed;

	};
}