#include "GameWorld.h"
#include "Menu.h"
#include "EndGameObject.h"


GameWorld::GameWorld() 
	:GameWorld("Game", 0.f, 9.8f)
{
}

GameWorld::GameWorld(std::string title, float X_gravity, float Y_gravity) 
	:	_window(GameParameters::WindowWidth, GameParameters::WindowHeight, title, X_gravity, Y_gravity),
		_player(_window, Game::Position(Game::CoordType::Pixel, 100, 100))
{
	_window.SetFrameRateLimit(60);
	//_entities.push_back(Player(_window));
}

void GameWorld::InstructionsScreen()
{

	sf::String rules = 
		"Use [WASD] or Arrows to Control Character.\n\Overcome obstacles and get to the flag";
	sf::Font font;
	font.loadFromFile("fonts\\AdobeFanHeitiStd-Bold.otf");
	sf::Text rulesText(rules, font, 30);
	sf::Event ev;
	while (true)
	{
		while (_window.PollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::EventType::KeyPressed:
				switch (ev.key.code)
				{
				case sf::Keyboard::Escape:
				case sf::Keyboard::Return:
					return;
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (ev.mouseButton.button)
				{
				case sf::Mouse::Left:
					return;
				}
				break;
			case sf::Event::Closed:
				GameClosing();
				break;
			default:
				break;
			}
		}
		rulesText.setPosition(
			_window.GetSize().GetX() / 2 - rulesText.getGlobalBounds().width / 2,
			_window.GetSize().GetY() / 2 - rulesText.getGlobalBounds().height / 2
		);
		_window.PrintString(rulesText);
		_window.Display();
	}
}

void GameWorld::Launch()
{
	GameMenu menu(_window, 70, { "Play", "Rules" ,"Exit" }, 40);
	do
	{
		_window.SetBackGround("textures//BG4.jpg");
		for (size_t input = menu.GetInput(_window); input != 0; input = menu.GetInput(_window))
		{
			switch (input)
			{
			case 1:
				InstructionsScreen();
				break;
			case 2:
			case -1:
				GameClosing();
			}
		}
		Initialize();
		_window.Step();
		while (_window.IsOpen())
		{
			for (std::list<BaseGameObject *>::iterator iterator = _entities.begin(); iterator != _entities.end();) // cycle walks through all game_elements and apply update
			{
				if ((*iterator)->update(_window) == false) // if update fails (object is expire), the object is removed from array
				{
					delete *iterator;
					std::list<BaseGameObject *>::iterator iterator_copy = iterator;
					iterator++;
					_entities.erase(iterator_copy);
					continue;
				}
				iterator++;
			}
			if (_player.update(_window) == false)
				break;
			_window.Display();
			_window.Step();
		}
		for (std::list<BaseGameObject *>::iterator iterator = _entities.begin(); iterator != _entities.end(); iterator++)
			delete *iterator;
		_entities.clear();
		_window.GameEnd();
		_window.MoveCamera(Game::Position(Game::CoordType::Pixel, 0, 0));
		_window.Display();
		LastScreen();
		
	}
	while (true);
		

}

void GameWorld::LastScreen()
{
	if (_player.isWin())
		_window.PlaySound("heart");
	sf::Event event;
	bool on = true;
	while (_window.PollEvent(event)); // clear events stack
	while (on)
	{
		while (_window.PollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					on = false;
					break;
				default:
					break;
				}
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
				case sf::Keyboard::Escape:
					on = false;
					break;
				default:
					break;
				}
				break;
			case sf::Event::Closed:
				GameClosing();
				break;
			default:
				break;
			}

		}
		_window.Display();
		_player.LastScreen(_window);
	}
}

void GameWorld::GameClosing()
{
	exit(0);
}


GameWorld::~GameWorld()
{
	for (std::list<BaseGameObject *>::iterator iterator = _entities.begin(); iterator != _entities.end(); iterator++) // cycle walks through all game_elements
		delete *iterator;
}

void GameWorld::Initialize() 
{
	_player.Reset(
		Game::Position(Game::CoordType::Pixel, 30, 300),
		_window.GetTime().asSeconds()
	);
	_player.AddSpawnPoints(
		{ 
			Game::Position(Game::CoordType::Pixel, 3500, 800),
			Game::Position(Game::CoordType::Pixel, 5397, 300)
		}
	);
	_window.SetBackGround("textures\\BG4.jpg");
	AnimationPack box_animation("textures\\box.png", 128, 128);
	AnimationPack platform_anim("textures\\StoneBlock.png");
	AnimationPack heart_anim("textures\\heart.png", 99, 90);
	AnimationPack big_platform_anim("textures\\big_platform.png");
	CircleAnimationPack coin_animation("textures\\coin.png", 62);
	CircleAnimationPack saw_anim("textures\\saw.png", 70);
	coin_animation.AddFrame("inaction", 0, 0);
	coin_animation.AddFrameSequence("inaction", 0, 0, 10, 0.1f, SpritesDir::RIGHT, 122, 122);
	CircleAnimationPack enemy_anim("textures\\enemy.png", 70);
	AnimationPack crate("textures\\crate.png");
	AnimationPack end_anim("textures\\flag.png");

	//adding Game objects to the list

	 //boxes
	_entities.push_back(new Box(_window, "box", GameObjectParameters(30, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(480, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 480, 300), coin_animation, false));

	_entities.push_back(new Heart(_window, Game::Position(Game::CoordType::Pixel, 980, 400), heart_anim, false));
	_entities.push_back(new Box(_window, "box", GameObjectParameters(980, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));

	
	_entities.push_back(new Box(_window, "box", GameObjectParameters(1280, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1280, 350, 1.0f, 1.f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 1280, 50), coin_animation, false));
	
	_entities.push_back(new Box(_window, "box", GameObjectParameters(1450, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1450, 350, 1.0f, 1.f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1450, 150, 1.0f, 1.f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 1450, 50), coin_animation, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(1620, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1620, 350, 1.0f, 1.f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1620, 150, 1.0f, 1.f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1620, 0, 1.0f, 1.f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 1620, -50), coin_animation, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(1790, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1790, 350, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1790, 150, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1790, 0, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(1790, -50, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 1790, -150), coin_animation, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(2250, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2250, 350, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2250, 150, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2250, 0, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2250, -50, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 2250, -150), coin_animation, false));

	_entities.push_back(new CircleEnemy(_window, Game::Position(Game::CoordType::Pixel, 2030, -150), saw_anim, 0, 8, 1, false, 18));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(2420, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2420, 350, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2420, 150, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2420, 0, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 2420, -50), coin_animation, false));
	
	_entities.push_back(new Box(_window, "box", GameObjectParameters(2590, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2590, 350, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2590, 150, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 2590, 50), coin_animation, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(2760, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Box(_window, "crate", GameObjectParameters(2760, 350, 1.0f, 1.0f, 0.1f, Game::BodyType::Dynamic), crate));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 2760, 50), coin_animation, false));


	_entities.push_back(new Platform(_window,Game::Position(Game::CoordType::Pixel, 3150, 350), big_platform_anim, 0, 3, 3.5f));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(3500, 1100, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 3500, 1000), coin_animation, false));

	_entities.push_back(new CircleEnemy(_window, Game::Position(Game::CoordType::Pixel, 3694, 600), enemy_anim, 0, 6, 1.3f, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(3900, 1100, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 3900, 1000), coin_animation, false));


	_entities.push_back(new CircleEnemy(_window, Game::Position(Game::CoordType::Pixel, 4094, 600), enemy_anim, 0, 6, 1.3f, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(4300, 1100, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 4300, 1000), coin_animation, false));

	_entities.push_back(new CircleEnemy(_window, Game::Position(Game::CoordType::Pixel, 4494, 600), enemy_anim, 0, 6, 1.3f, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(4700, 1100, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));
	_entities.push_back(new Heart(_window, Game::Position(Game::CoordType::Pixel, 4700, 1000), heart_anim, false));

	_entities.push_back(new Platform(_window, Game::Position(Game::CoordType::Pixel, 5050, 350), big_platform_anim, 0, 3, 3.5f));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 5050, 250), coin_animation, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(5400, 500, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));

	_entities.push_back(new Platform(_window, Game::Position(Game::CoordType::Pixel, 5800, 300), platform_anim, 0.f, 2.f, 5.f));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 5800, 0), coin_animation, false));

	_entities.push_back(new CircleEnemy(_window, Game::Position(Game::CoordType::Pixel, 6009, 300), saw_anim, 0, 10, 1.25f, false, 18));

	_entities.push_back(new Platform(_window, Game::Position(Game::CoordType::Pixel, 6220, 300), platform_anim, 0.f, 2.f, 5.f));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 6220, 0), coin_animation, false));

	_entities.push_back(new CircleEnemy(_window, Game::Position(Game::CoordType::Pixel, 6429, 300), saw_anim, 0, 10, 1.25f, false, 18));

	_entities.push_back(new Platform(_window, Game::Position(Game::CoordType::Pixel, 6640, 300), platform_anim, 0.f, 2.f, 5.f));
	_entities.push_back(new Coin(_window, Game::Position(Game::CoordType::Pixel, 6640, 0), coin_animation, false));

	_entities.push_back(new Box(_window, "box", GameObjectParameters(7070, 800, 2.0f, 1.f, 0.1f, Game::BodyType::Static), box_animation));

	_entities.push_back(new EndGameObject(_window, Game::Position(Game::CoordType::Pixel, 7135, 635), end_anim));

	
	
}
