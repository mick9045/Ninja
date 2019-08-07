#pragma once
#include "SFML\Graphics.hpp"
#include "Settings.h"
#include <vector>
#include "GameWindow.h"
#include <initializer_list>

class GameMenu
{
public:
	GameMenu(Game::Window & window, WORD yOffset, std::initializer_list<std::string> titles, WORD font_size);
	void SetActiveColor(sf::Color color);
	void SetInactiveColor(sf::Color color);
	sf::Color GetInactiveColor();
	sf::Color GetActiveColor();
	int GetInput(Game::Window & window); // method getsuser input and returns menu element index
private:
	void CalculateTitlesPos(Game::Window & window);
	sf::Font _font;
	std::vector<sf::Text> _titles;
	
	int _active_element;
	sf::Color _active_element_color;
	sf::Color _inactive_element_color;
	WORD _fontSize;
	WORD _yOffset;
};

