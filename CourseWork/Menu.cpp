#include "Menu.h"
#include <iostream>


GameMenu::GameMenu(Game::Window & window,
				   WORD yOffset,
				   std::initializer_list<std::string> titles,
				   WORD font_size)
{
	bool result;
	const char* fontPath = "fonts//AdobeFanHeitiStd-Bold.otf";
	result = _font.loadFromFile(fontPath);
	if (!result)
	{
		std::cerr << "failed to load font " << fontPath;
	}
	_active_element = 0;
	_active_element_color = sf::Color::Cyan;
	_inactive_element_color = sf::Color::White;

	for each (auto title in titles)
	{
		_titles.push_back(sf::Text(title, _font, font_size));
	}
	_yOffset = yOffset;
	CalculateTitlesPos(window);
}

void GameMenu::CalculateTitlesPos(Game::Window & window)
{
	int i = 0;
	Game::Position screenPos = Game::Position(
		Game::CoordType::Pixel,
		window.GetSize().GetX() / 2,
		window.GetSize().GetY() / 3
	);
	sf::Vector2f cameraPos = window.GetCameraLeftTopPosition().GetPixelPos();
	sf::Vector2f textPosition;

	_titles[_active_element].setColor(_active_element_color);
	for (int i = 0; i < _titles.size(); i++)
	{
		if (i == 0)
		{
			screenPos.Set(
				Game::CoordType::Pixel,
				screenPos.GetPixelPos().x - (_titles[0].getGlobalBounds().width / 2),
				screenPos.GetPixelPos().y
			);
		}
		
		
		textPosition = sf::Vector2f(
			cameraPos.x + screenPos.GetPixelPos().x,
			cameraPos.y + screenPos.GetPixelPos().y
		);
		screenPos.Set(
			Game::CoordType::Pixel,
			screenPos.GetPixelPos().x,
			screenPos.GetPixelPos().y + _yOffset
		);
		_titles[i].setPosition(textPosition);
	}
}

void GameMenu::SetActiveColor(sf::Color color)
{
	_active_element_color = color;
}

void GameMenu::SetInactiveColor(sf::Color color)
{
	_inactive_element_color = color;
}

sf::Color GameMenu::GetInactiveColor()
{
	return _inactive_element_color;
}

sf::Color GameMenu::GetActiveColor()
{
	return _active_element_color;
}

int GameMenu::GetInput(Game::Window & window)
{
	static sf::Time last_press = window.GetTime();
	static int last_active = 0;
	sf::Event event;
	CalculateTitlesPos(window);
	while (window.PollEvent(event)); // clear events stack
	
	while (true)
	{
		for (std::vector<sf::Text>::iterator iterator = _titles.begin(); iterator != _titles.end(); iterator++)
		{
			window.PrintString(*iterator);
		}

		while (window.PollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					if (window.GetTime().asSeconds() - last_press.asSeconds() < 0.1f)
						break;
					last_press = window.GetTime();
					last_active = _active_element;
					_active_element++;
					if (_active_element > _titles.size() - 1)
						_active_element = 0;
					_titles[last_active].setColor(_inactive_element_color);
					_titles[_active_element].setColor(_active_element_color);
					window.PlaySound("jump");
					break;

				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					if (window.GetTime().asSeconds() - last_press.asSeconds() < 0.1f)
						break;
					last_press = window.GetTime();
					last_active = _active_element;
					_active_element--;
					if (_active_element < 0)
						_active_element = _titles.size() - 1;
					_titles[last_active].setColor(_inactive_element_color);
					_titles[_active_element].setColor(_active_element_color);
					window.PlaySound("jump");
					break;
				case sf::Keyboard::Return :
					window.Clear();
					return _active_element;
				case sf::Keyboard::Escape:
					while (window.PollEvent(event));
					return -2;
				}
				break;
			case sf::Event::Closed:
				return -1;
			case sf::Event::Resized:
			{
				CalculateTitlesPos(window);
				break;
			}
			case sf::Event::MouseMoved:
				for (int i = 0; i < _titles.size(); i++)
				{
					sf::Vector2f mousePos(
						event.mouseMove.x + window.GetCameraLeftTopPosition().GetPixelPos().x,
						event.mouseMove.y + window.GetCameraLeftTopPosition().GetPixelPos().y
					);
					if (_titles[i].getGlobalBounds().contains(mousePos))
					{
						if (last_active != i)
							window.PlaySound("jump");
						last_active = _active_element;
						_titles[last_active].setColor(_inactive_element_color);
						_active_element = i;
						_titles[i].setColor(_active_element_color);
						
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < _titles.size(); i++)
					{
						sf::Vector2f mousePos(
							event.mouseButton.x + window.GetCameraLeftTopPosition().GetPixelPos().x,
							event.mouseButton.y + window.GetCameraLeftTopPosition().GetPixelPos().y
						);
						if (_titles[i].getGlobalBounds().contains(mousePos))
						{
							return i;
						}
					}
				}
				break;
			default:
				break;
			}
		}
		window.Display();
		
	}
	return _active_element;
}


