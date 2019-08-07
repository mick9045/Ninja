#pragma once


typedef unsigned short WORD;


namespace GameParameters
{
	const float scaling = 0.013f;
	const WORD WindowWidth = 1024;
	const WORD WindowHeight = 768;
	enum OBJ_TYPE
	{
		SENSOR = 0x01,
		PLAYER = 0x02
	};
}
