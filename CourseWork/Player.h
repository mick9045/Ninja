#pragma once
#include "Box.h"
#include <SFML\Audio.hpp>

class Player
	: public Box
{
public:
	Player(Game::Window & window, Game::Position const & spawn_point);
	virtual bool update(Game::Window & window);
	void LastScreen(Game::Window & window);
	void AddSpawnPoints(std::initializer_list<Game::Position> positions);
	void Reset(Game::Position const & spawn_point, float gameStartTime);
	bool isWin();
private:
	bool CollisionCheck(Game::Window &window);
	void UpdateScreenInfo(Game::Window & window);
	WORD _lives;
	WORD _coins;
	std::vector<Game::Position> _spawn_points;
	WORD _active_spawn_point;
	sf::Font _font;
	sf::Texture _info_table_texure;
	sf::Sprite _info_table_sprite;
	sf::Clock _exitMenuClock;
	float _gameStartTime;
	struct PlayerFlags
	{
		bool in_the_air = false;
		bool flip = false;
		bool win = false;
		sf::Time jump_time;
		int gameLength;
	} _flags;
};

