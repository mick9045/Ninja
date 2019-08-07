#include "Animation.h"
#include "GameWindow.h"
#include <iostream>


AnimationPack::AnimationPack(std::string const & file_path, WORD frame_width, WORD frame_height)
{
	try
	{
		_texture = std::make_shared<sf::Texture>();
	}
	catch (std::bad_alloc bad_alloc)
	{
		std::clog << bad_alloc.what();
		return;
	}
	if (_texture->loadFromFile(file_path) == false)
	{
		std::clog << "can't load texture " << file_path;
		return;
	}
	_frame_width = frame_width;
	_frame_height = frame_height;
	_sprite.setTexture(*_texture);
}

AnimationPack::AnimationPack(std::shared_ptr<sf::Texture> & texture, WORD frame_width, WORD frame_height)
{
	_texture = texture;
	_frame_width = frame_width;
	_frame_height = frame_height;
	_sprite.setTexture(*_texture);
}

AnimationPack::AnimationPack(std::shared_ptr<sf::Texture>& texture)
{
	_texture = texture;
	_frame_width = _texture->getSize().x;
	_frame_height = _texture->getSize().y;
	_sprite.setTexture(*_texture);
}

AnimationPack::AnimationPack(std::string const & image_path)
{
	try
	{
		_texture = std::make_shared<sf::Texture>();
	}
	catch (std::bad_alloc bad_alloc)
	{
		std::clog << bad_alloc.what();
		return;
	}
	if (_texture->loadFromFile(image_path) == false)
	{
		std::clog << "can't load texture " << image_path;
		return;
	}
	_frame_width = _texture->getSize().x;
	_frame_height = _texture->getSize().y;
	_sprite.setTexture(*_texture);
}

bool AnimationPack::ReloadSprite(std::string const & image_path)
{
	sf::Texture texture;
	if (texture.loadFromFile(image_path) == false)
	{
		std::clog << "can't load texture " << image_path;
		return false;
	}
	_sprite.setTexture(texture);
	return true;
}

void AnimationPack::ReloadSprite(sf::Texture const & texture)
{
	_sprite.setTexture(texture);
}

void AnimationPack::Draw(Game::Window & window, Game::Position pos, float angle, bool flip)
{
	sf::Vector2f origin;
	if (_active.length() == 0)
	{
		_sprite.setTextureRect(sf::IntRect(0, 0, _frame_width, _frame_height));
		_sprite.setOrigin(_frame_width / 2, _frame_height / 2);
	}
	else if (_frames[_active].GetFramesCount() == 0)
	{
		std::cout << "can't draw empty frame";
		return;
	}
	else {
		PictureFrames frame = _frames[_active];
		_frames[_active].SetGetFlip() = flip;
		
		_sprite.setTextureRect(_frames[_active].GetFrame());
		_sprite.setOrigin(_frame_width / 2, _frame_height / 2);
	}
	_sprite.getTextureRect();
	_sprite.setRotation(angle);
	_sprite.setPosition(pos.GetPixelPos().x, pos.GetPixelPos().y);
	window.Draw(_sprite);
	
}

Game::Size AnimationPack::TextureSize()
{
	return Game::Size();
}

bool AnimationPack::SetActive(std::string name)
{

	if (_frames.count(name) == 0)
	{
		std::clog << "no frames with such name: " << name;
		return false;
	}
	_active = name;
	return true;
}

bool AnimationPack::AddFrameSequence(std::string name, WORD pos_x, WORD pos_y,  WORD count, float speed, SpritesDir sprites_dir, WORD frame_width, WORD frame_height)
{
	if (_active.length() == 0)
		_active = name;
	switch (sprites_dir)
	{
	case SpritesDir::DOWN:
		if (pos_x + frame_width > _texture->getSize().x) {
			std::clog << "frame is beyond limits (width) " << name;
			return false;
		}
		else if (pos_y + frame_height * count > _texture->getSize().y) {
			std::clog << "frame is beyond limits (height) " << name;
			return false;
		}
		break;
	case SpritesDir::RIGHT :
		if (pos_y + frame_height > _texture->getSize().y) {
			std::clog << "frame is beyond limits (height) " << name;
			return false;
		}
		else if (pos_x + frame_width * count > _texture->getSize().x) {
			std::clog << "frame is beyond limits (width) " << name;
			return false;
		}
		break;
	case SpritesDir::UP:
		if (pos_x + frame_width > _texture->getSize().x) {
			std::clog << "frame is beyond limits (width) " << name;
			return false;
		}
		else if (pos_y - frame_height * count < 0) {
			std::clog << "frame is beyond limits (height) " << name;
			return false;
		}
		break;
	case SpritesDir::LEFT:
		if (pos_y + frame_height > _texture->getSize().y) {
			std::clog << "frame is beyond limits (height)" << name;
			return false;
		}
		if (pos_x - frame_width * count < 0) {
			std::clog << "frame is beyond limits (width)" << name;
		}
		break;
	}
	_frames[name] = PictureFrames(pos_x, pos_y, frame_width, frame_height, count, sprites_dir, speed);
	return true;
}

bool AnimationPack::AddFrame(std::string name, WORD pos_x, WORD pos_y, WORD frame_width, WORD frame_height)
{
	if (_active.length() == 0)
		_active = name;
	if (pos_x + frame_width > _texture->getSize().x) {
		std::clog << "frame is beyond limits (width)";
		return false;
	}
	if (pos_y + frame_height > _texture->getSize().y) {
		std::clog << "frame is beyond limits (height)";
		return false;
	}
	_frames[name].AddFrame(pos_x, pos_y, frame_width, frame_height);
	return true;
}

bool AnimationPack::AddFrameSequence(std::string name, WORD pos_x, WORD pos_y, WORD count, float speed, SpritesDir sprites_dir)
{
	return AddFrameSequence(name,pos_x, pos_y, count, speed, sprites_dir, _frame_width, _frame_height);
}

bool AnimationPack::AddFrame(std::string name, WORD pos_x, WORD pos_y)
{
	return AddFrame(name, pos_x, pos_y, _frame_width, _frame_height);
}

void AnimationPack::SetLoop(std::string name, bool loop)
{
	_frames[name].SetGetLoop() = loop;
}

bool AnimationPack::GetLoop(std::string name)
{
	return _frames[name].SetGetLoop();
}

bool AnimationPack::Replay(std::string name)
{
	if (_frames.count(name) == 0)
	{
		std::clog << "no frames with such name: " << name;
		_frames[name].FromStart();
		return false;
	}
	_frames[name].FromStart();
	return true;
}

bool AnimationPack::Replay()
{
	if (_frames.count(_active) == 0)
	{
		std::clog << "empty animation";
		return false;
	}
	_frames[_active].FromStart();
	return true;
}



WORD AnimationPack::GetFrameWidth() const
{
	return _frame_width;
}

WORD AnimationPack::GetFrameHeight() const
{
	return _frame_height;
}


CircleAnimationPack::CircleAnimationPack(std::string const & image_path, WORD circle_radius)
	: AnimationPack(image_path, circle_radius * 2, circle_radius * 2)
{
}

CircleAnimationPack::CircleAnimationPack(std::shared_ptr<sf::Texture> & texture, WORD cirlce_radius)
	: AnimationPack(texture,  cirlce_radius * 2, cirlce_radius * 2)
{
}

WORD CircleAnimationPack::GetTextureRadius() const
{
	return _frame_height / 2;
}
