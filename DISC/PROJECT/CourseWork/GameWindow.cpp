#include "GameWindow.h"
#include <iostream>

namespace Game
{
	Window::Window(WORD width, WORD height, std::string title, float32 x_gravity, float32 y_gravity)
		:_world(b2Vec2(x_gravity, y_gravity))
	{
		_window.create(sf::VideoMode(width, height), title);
		_world_step = 1.f / 60.f;
		
		sf::Image Icon;
		if (Icon.loadFromFile("resources\\ninja.png"))
			_window.setIcon(32, 32, Icon.getPixelsPtr());

		sf::SoundBuffer soundBuffer = sf::SoundBuffer();
		soundBuffer.loadFromFile("audio\\Coins.wav");
		_soundBufferMap["coin"] = soundBuffer;
		soundBuffer.loadFromFile("audio\\1up.wav");
		_soundBufferMap["heart"] = soundBuffer;
		soundBuffer.loadFromFile("audio\\jump2.wav");
		_soundBufferMap["jump"] = soundBuffer;
		
		//_soundBufferMap[0].loadFromFile("audio\\Coins.wav");
	}

	Window::Window(WORD width, WORD height, std::string title, WORD frame_rate_limit, float32 x_gravity, float32 y_gravity)
		:Window(width, height, title, x_gravity, y_gravity)
	{
		_window.setFramerateLimit(frame_rate_limit);
		_world_step = 1.f / frame_rate_limit;
	}
	
	Game::Position Window::GetPostion()
	{
		return Game::Position(Game::CoordType::Pixel, _window.getPosition().x, _window.getPosition().y);
	}

	Game::Size Window::GetSize()
	{
		return Game::Size(Game::CoordType::Pixel, _window.getSize().x, _window.getSize().y);
	}

	void Window::Draw(sf::Sprite const & sprite)
	{
		
		_window.draw(sprite);
	}

	b2World & Window::GetWorld()
	{
		return _world;
	}

	KEYBOARD_ACTION Window::GetKeyboardAction()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			return KEYBOARD_ACTION::Up;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			return KEYBOARD_ACTION::Jump;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			return KEYBOARD_ACTION::Down;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			return KEYBOARD_ACTION::Right;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			return KEYBOARD_ACTION::Left;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return KEYBOARD_ACTION::Exit;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			return KEYBOARD_ACTION::Enter;
		else
			return KEYBOARD_ACTION::Inaction;
	}

	Position Window::GetMousePosition()
	{
		return Game::Position(
			Game::CoordType::Pixel,
			sf::Mouse::getPosition(_window).x,
			sf::Mouse::getPosition(_window).y
		);
	}

	MOUSE_ACTION Window::GetMouseAction()
	{
		if (_wheel_delta != 0)
		{
			int temp_value = _wheel_delta;
			_wheel_delta = 0;
			return temp_value < 0 ? MOUSE_ACTION::WheelDown : MOUSE_ACTION::WheelUp;
		}
		if (_wheel_delta > 0)
		{
			_wheel_delta = 0;
			return MOUSE_ACTION::WheelUp;
		}
		else if (_wheel_delta < 0)
		{
			_wheel_delta = 0;
			return MOUSE_ACTION::WheelDown;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			return MOUSE_ACTION::RightButton;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return MOUSE_ACTION::LeftButton;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
			return MOUSE_ACTION::MiddleButton;
		else
			return MOUSE_ACTION::Inaction;
	}

	void Window::MoveCamera(Game::Position position)
	{
		sf::View view(sf::FloatRect(sf::Vector2f(position.GetPixelPos().x, position.GetPixelPos().y), sf::Vector2f(_window.getSize())));
		_back_ground_sprite.setPosition(position.GetPixelPos().x, position.GetPixelPos().y);
		_window.setView(view);
	}
	
	void Window::MoveCamera(float pos_px_x, float pos_px_y)
	{
		sf::View view(sf::FloatRect(sf::Vector2f(pos_px_x, pos_px_y), sf::Vector2f(_window.getSize())));
		_back_ground_sprite.setPosition(pos_px_x, pos_px_y);
		_window.setView(view);
	}

	bool Window::IsOpen()
	{
		if (_window.isOpen() == false)
			return false;
		sf::Event _event;
		while (_window.pollEvent(_event))
		{
			switch (_event.type)
			{
			case sf::Event::Closed:
				Close();
				exit(0);
			case sf::Event::MouseWheelMoved:
				this->_wheel_delta = _event.mouseWheel.delta;
				break;
			default:
				break;
			}
			
		}
		return true;
	}

	Game::Position Window::GetCameraLeftTopPosition() const
	{
		return Game::Position(
			Game::CoordType::Pixel,
			_window.getView().getCenter().x - (_window.getSize().x / 2),
			_window.getView().getCenter().y - (_window.getSize().y / 2)
		);
	}

	bool Window::PollEvent(sf::Event & event)
	{
		if (!_window.pollEvent(event))
			return false;
		switch (event.type)
		{
		case sf::Event::Resized:
		{
			UpdateView(
				Game::Size(event.size.width, event.size.height)
			);
			break;
		}
		default:
			break;
		}
		return true;
	}

	void Window::Clear()
	{
		_window.clear();
	}

	bool Window::PlaySound(std::string soundName)
	{
		if (_soundBufferMap.count(soundName) != 1)
		{
			return false;
		}
		_sound.setBuffer(_soundBufferMap[soundName]);
		_sound.play();
		return true;
	}

	void Window::Close()
	{
		_window.close();
	}

	void Window::SetFrameRateLimit(WORD limit)
	{
		_window.setFramerateLimit(limit);
		_world_step = 1.f / limit;
	}

	void Window::Display()
	{
		_window.display();
		_window.clear();
		DrawBackground();
	}

	void Window::DrawBackground()
	{
		float xScale =
			GetSize().GetPixelPos().x
				/
			_back_ground_sprite.getGlobalBounds().width;
		float yScale = 
			GetSize().GetPixelPos().y
				/
			_back_ground_sprite.getGlobalBounds().height;
		_back_ground_sprite.scale(xScale, yScale);
		
		_window.draw(_back_ground_sprite);
	}

	void Window::Step()
	{
		_world.Step(_world_step, 8, 3);
	}

	void Window::UpdateView(Game::Size newSize)
	{
		sf::FloatRect rect = sf::FloatRect(
			0, 0,
			newSize.GetX(),
			newSize.GetY()
		);
		_window.setView(sf::View(rect));
		MoveCamera(0, 0);
	}


	void Window::SetGravity(float32 x_gravity, float32 y_gravity)
	{
		_world.SetGravity(b2Vec2(x_gravity, y_gravity));
	}

	sf::Time Window::GetTime()
	{
		return _clock.getElapsedTime();
	}

	void Window::SetBackGround(std::string path)
	{
		_back_ground_texture.loadFromFile(path);
		_back_ground_texture.setSmooth(true);
		_back_ground_sprite.setTexture(_back_ground_texture, true);
	}

	void Window::PrintString(sf::Text const & text)
	{
		_window.draw(text);
	}

	void Window::GameEnd()
	{
		_window.clear();
	}

}