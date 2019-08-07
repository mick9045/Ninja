#include "AnimationFrames.h"
#include <iostream>





PictureFrames::PictureFrames(WORD pos_x, WORD pos_y, WORD width, WORD height, WORD count, SpritesDir dir, float speed)
{
	_speed = speed;
	_frames_count = 0;
	AddFramesSequence(pos_x, pos_y, width, height, count, dir);
	_loop = true;
	_flip = false;
	_current_frame = 0;
}

PictureFrames::PictureFrames()
{
	_loop = true;
	_speed = 0.05f;
	_current_frame = 0;
	_frames_count = 0;
}

PictureFrames::~PictureFrames()
{
}

void PictureFrames::AddFrame(float pos_x, float pos_y, WORD width, WORD height)
{
	_frames.push_back(sf::IntRect(pos_x, pos_y, width, height));
	_frames.push_back(sf::IntRect(pos_x + width, pos_y, -static_cast<int>(width), height));
	_frames_count++;
}

void PictureFrames::AddFramesSequence(WORD pos_x, WORD pos_y, WORD width, WORD height, WORD count, SpritesDir dir)
{
	_frames_count += count;
	switch (dir)
	{
	case SpritesDir::DOWN:
		for (WORD i = 0; i < _frames_count; i++)
		{
			_frames.push_back(sf::IntRect(pos_x, pos_y + height * i, width, height));
			_flip_frames.push_back(sf::IntRect(pos_x + width, pos_y + height * i, -static_cast<int>(width), height));
		}
		break;
	case SpritesDir::RIGHT:
		for (WORD i = 0; i < _frames_count; i++)
		{
			_frames.push_back(sf::IntRect(pos_x + width * i, pos_y, width, height));
			_flip_frames.push_back(sf::IntRect(pos_x + width * i + width, pos_y, -static_cast<int>(width), height));
		}
		break;
	case SpritesDir::UP:
		for (WORD i = 0; i < _frames_count; i++)
		{
			_frames.push_back(sf::IntRect(pos_x, pos_y - height * i, width, height));
			_flip_frames.push_back(sf::IntRect(pos_x + width, pos_y - height * i, -static_cast<int>(width), height));
		}
		break;
	case SpritesDir::LEFT:
		for (WORD i = 0; i < _frames_count; i++)
		{
			_frames.push_back(sf::IntRect(pos_x - width * i, pos_y, width, height));
			_flip_frames.push_back(sf::IntRect(pos_x - width * i + width, pos_y, -static_cast<int>(width), height));
		}
		break;
	}
}


sf::IntRect PictureFrames::GetFrame()
{
	if (_frames_count == 0) {
		return sf::IntRect(0, 0, 0, 0);
		std::clog << "no frames";
	}
	int temp_frame = _current_frame;
	_current_frame += _speed;
	if (_current_frame > _frames_count - 1 && _loop == false)
		_current_frame = _frames_count - 1;
	else if (_current_frame > _frames_count - 1) 
		_current_frame -= _frames_count;
	return _flip == false ? _frames[static_cast<WORD> (temp_frame)] : _flip_frames[static_cast<WORD> (temp_frame)];
}

WORD PictureFrames::GetFramesCount()
{
	return _frames_count;
}

float PictureFrames::GetSpeed()
{
	return _speed;
}

void PictureFrames::Flip()
{
	_flip == false ? _flip = true : _flip = false;
}



void PictureFrames::SetSpeed(float speed)
{
	_speed = speed;
}

void PictureFrames::FromStart()
{
	_current_frame = 0;
}

bool & PictureFrames::SetGetLoop()
{
	return _loop;
}

bool & PictureFrames::SetGetFlip()
{
	//std::cin.get();
	return _flip;
}

