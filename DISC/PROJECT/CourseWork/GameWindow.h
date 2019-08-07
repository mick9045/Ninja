#pragma once
#include "Coord.h"
#include <SFML\Audio.hpp>

namespace Game
{
	enum class KEYBOARD_ACTION
	{
		Up, Down, Right, Left, Jump, Inaction, Enter, Exit
	};
	enum class MOUSE_ACTION
	{
		RightButton, LeftButton, WheelUp, WheelDown, MiddleButton, Inaction
	};

	class Window
	{
	public:
		Window(WORD width, WORD height, std::string title, float32 x_gravity = 0, float32 y_gravity = 9.8);
		Window(WORD width, WORD height, std::string title, WORD frame_rate_limit, float32 x_gravity = 0, float32 y_gravity = 9.8);
		Game::Position GetPostion();
		Game::Size GetSize();
		void Draw(sf::Sprite const & sprite);
		b2World & GetWorld();
		KEYBOARD_ACTION GetKeyboardAction();
		Position GetMousePosition();
		MOUSE_ACTION GetMouseAction();
		void MoveCamera(Game::Position position);
		void MoveCamera(float pos_px_x, float pos_px_y);
		void Clear();
		bool PlaySound(std::string soundName);
		void Close();
		void SetFrameRateLimit(WORD limit);
		void Display();	
		void DrawBackground();
		void Step();
		void UpdateView(Game::Size);
		void SetGravity(float32 x_gravity, float32 y_gravity);
		sf::Time GetTime();
		void SetBackGround(std::string path);
		void PrintString(sf::Text const & text);
		void GameEnd();
		bool IsOpen();
		Game::Position GetCameraLeftTopPosition() const;
		bool PollEvent(sf::Event & event);
	private:
		sf::RenderWindow _window;
		b2World _world;
		float32 _world_step;
		int _wheel_delta;
		sf::Clock _clock;
		sf::Texture _back_ground_texture;
		sf::Sprite _back_ground_sprite;
		std::map<std::string, sf::SoundBuffer> _soundBufferMap;
		sf::Sound _sound;
	};
}