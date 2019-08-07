#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Settings.h"
#include "Coord.h"


enum class SpritesDir
{
	DOWN, RIGHT, UP, LEFT
};

class PictureFrames // storage of frame borders
{
public:
	PictureFrames(WORD pos_x, WORD pos_y, WORD width, WORD height, WORD count, SpritesDir dir, float speed = 0.05);
	PictureFrames();
	~PictureFrames();
	void AddFrame(float pos_x, float pos_y, WORD width, WORD height);
	void AddFramesSequence(WORD pos_x, WORD pos_y, WORD width, WORD height, WORD count, SpritesDir dir);
	sf::IntRect GetFrame(); // return the border of frame to draw
	WORD GetFramesCount();
	float GetSpeed();
	void Flip();
	void SetSpeed(float speed);
	void FromStart();
	bool & SetGetLoop();
	bool & SetGetFlip();
private:
	std::vector<sf::IntRect> _frames, _flip_frames;
	WORD _frames_count;
	float _current_frame;
	bool _flip;
	float _speed;
	bool _loop;
};

