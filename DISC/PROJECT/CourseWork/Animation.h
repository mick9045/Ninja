#pragma once
#include "AnimationFrames.h"
#include <map>
#include <string>
#include <iostream>
#include <memory>
#include "GameWindow.h"

class AnimationPack
{
public:
	AnimationPack(std::string const & image_path, WORD frame_width, WORD frame_height);
	AnimationPack(std::shared_ptr<sf::Texture> & texture, WORD frame_width, WORD frame_height);
	AnimationPack(std::shared_ptr<sf::Texture> & texture);
	AnimationPack(std::string const & image_path);
	bool ReloadSprite(std::string const & image_path);
	void ReloadSprite(sf::Texture const & texture);
	void Draw(Game::Window & window, Game::Position pos, float angle, bool flip = false);
	Game::Size TextureSize();
	WORD GetFrameWidth() const;
	WORD GetFrameHeight() const;
	bool SetActive(std::string name);
	bool AddFrameSequence(std::string name, WORD pos_x, WORD pos_y, WORD count,
			float speed, SpritesDir sprites_dir, WORD frame_width, WORD frame_height);
	bool AddFrame(std::string name, WORD pos_x, WORD pos_y, WORD frame_width, WORD frame_height);
	bool AddFrameSequence(std::string name, WORD pos_x, WORD pos_y, WORD count,
			float speed, SpritesDir sprites_dir);
	bool AddFrame(std::string name, WORD pos_x, WORD pos_y);

	void SetLoop(std::string name, bool loop);
	bool GetLoop(std::string name);
	bool Replay(std::string);
	bool Replay();

protected:
	std::map<std::string, PictureFrames> _frames;
	WORD _frame_width, _frame_height;
	float32 _sprite_scale;
	std::string _active;
	std::shared_ptr<sf::Texture> _texture;
	sf::Sprite _sprite;
	
};

class CircleAnimationPack
	:public AnimationPack
{
public:
	CircleAnimationPack(std::string const & image_path, WORD circle_radius);
	CircleAnimationPack(std::shared_ptr<sf::Texture> & texture, WORD cirlce_radius);
	WORD GetTextureRadius() const;
};
