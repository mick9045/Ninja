#include "Player.h"
#include "Menu.h"

Player::Player(Game::Window  & window, Game::Position const & spawn_point)
	: Box (
		window,
		"player",
		GameObjectParameters(6, 6, 1.0f, 1.f, 0.01f, Game::BodyType::Dynamic),
		AnimationPack("textures\\ninja_base5.png", 77, 146)
	)
{	
	_body->SetBullet(true);
	_lives = 0;
	_coins = 0;
	_active_spawn_point = 0;
	_flags.win = false;
	_gameStartTime = window.GetTime().asSeconds();

	_font.loadFromFile("fonts//AdobeFanHeitiStd-Bold.otf");
	_info_table_texure.loadFromFile("textures//info_table.png");
	_info_table_sprite.setTexture(_info_table_texure);
	_spawn_points.push_back(spawn_point);
	_body->SetFixedRotation(true);

	_animation_pack.AddFrameSequence("stay", 0, 0, 10, 0.1f, SpritesDir::DOWN, 77, 146);
	_animation_pack.AddFrameSequence("walk", 78, 0, 10, 0.3f, SpritesDir::DOWN, 121, 153);
	_animation_pack.AddFrameSequence("jump", 199, 0, 10, 0.4f, SpritesDir::DOWN, 121, 161);
	_animation_pack.SetLoop("jump", false);

	b2Vec2 vec = b2Vec2(
		_spawn_points[_active_spawn_point].GetPhysicsPos().x,
		_spawn_points[_active_spawn_point].GetPhysicsPos().y
	);
	_body->SetTransform(vec, 0);
	_animation_pack.SetActive("stay");

}

bool Player::CollisionCheck(Game::Window &window)
{

	if (_body->GetPosition().y / GameParameters::scaling > 1600) // check if player fell
	{
		if (_lives > 0)
		{
			_lives--;
			b2Vec2 vec = _spawn_points[_active_spawn_point].GetPhysicsPos();
			_body->SetTransform(vec, 0);
			_body->SetLinearVelocity(b2Vec2(0, 0));
			_body->SetAngularVelocity(0);
		}
		else
		{
			_flags.gameLength = window.GetTime().asSeconds() - _gameStartTime;
			return false;
		}
	}

	for (int i = _active_spawn_point; i < _spawn_points.size(); i++)
	{
		if (_body->GetPosition().x >= _spawn_points[i].GetPhysicsPos().x)
			_active_spawn_point = i;
	}
		

	for (b2ContactEdge * contact = _body->GetContactList(); contact != nullptr; contact = contact->next)
	{
		std::string objectBName = static_cast<BaseGameObject *>(contact->contact->GetFixtureB()->GetBody()->GetUserData())->GetName();
		b2Body * objectBBody = contact->contact->GetFixtureB()->GetBody();
		

		if (objectBName == "box" || objectBName == "platform" || objectBName == "crate")
		{
			/*
			b2WorldManifold manifold;
			contact->contact->GetWorldManifold(&manifold);
			if (round(manifold.points[0].y * 100) / 100 != round(manifold.points[1].y * 100) / 100) break;
			*/
			b2PolygonShape* polygonA = (b2PolygonShape*)(contact->contact->GetFixtureA()->GetShape());
			b2PolygonShape* polygonB = (b2PolygonShape*)(contact->contact->GetFixtureB()->GetShape());
			
			if (abs((objectBBody->GetPosition().y + polygonB->GetVertex(1).y) - (_body->GetPosition().y + polygonA->GetVertex(3).y)) < 0.5)
			{

				if (_flags.in_the_air == true && contact->contact->IsTouching())
				{
					_flags.in_the_air = false;
					//window.PlaySound("heart");
					_body->SetLinearVelocity(b2Vec2(0, 10));
					//_body->ApplyForceToCenter(b2Vec2(0, -20), true);
				}
			}
		}
		if (objectBName == "coin")
		{
			_coins++;
			window.PlaySound("coin");
		}
		if (objectBName == "heart")
		{
			_lives++;
			window.PlaySound("heart");
		}
		if (objectBName == "enemy" && contact->contact->IsTouching())
		{
			if (_lives > 0)
			{
				_lives--;
				_body->SetLinearVelocity(b2Vec2(0, 0));
				b2Vec2 transform = b2Vec2(
					_spawn_points[_active_spawn_point].GetPhysicsPos().x,
					_spawn_points[_active_spawn_point].GetPhysicsPos().y
				);
				_body->SetLinearVelocity(b2Vec2(0, 0));
				_body->SetTransform(transform , 0);

			}
			else
			{
				_flags.gameLength = window.GetTime().asSeconds() - _gameStartTime;
				return false;
			}
		}
		if (objectBName == "end" && contact->contact->IsTouching())
		{
			_flags.gameLength = window.GetTime().asSeconds() - _gameStartTime;
			_flags.win = true;
			return false;
		}
		

	}
	if (_body->GetContactList() == nullptr)
		_flags.in_the_air = true;
	return true;
}

void Player::UpdateScreenInfo(Game::Window & window)
{
	sf::Vector2f info_pos(
		window.GetCameraLeftTopPosition().GetPixelPos().x,
		window.GetCameraLeftTopPosition().GetPixelPos().y
	);
	sf::Vector2f timer_pos(
		info_pos.x + window.GetSize().GetPixelPos().x,
		info_pos.y + 5);
	//sprite show heart
	_info_table_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	char number_string[8];

	//heart
	_itoa_s(_lives, number_string, 8, 10);
	sf::String string;
	info_pos.y += 10;
	info_pos.x += 4;
	string += "x ";
	string += number_string;
	sf::Text title(string, _font, 30);
	_info_table_sprite.setPosition(info_pos);
	info_pos.y += 64 / 2;
	info_pos.x += 64;
	title.setPosition(info_pos);
	title.setColor(sf::Color::Red);
	window.PrintString(title);
	window.Draw(_info_table_sprite);

	//coins
	_itoa_s(_coins, number_string, 8, 10);
	string.clear();
	string += "x ";
	string += number_string;
	info_pos.y += 45;
	info_pos.x -= 64;
	_info_table_sprite.setPosition(info_pos);
	info_pos.x += 64;
	info_pos.y += 64 / 2;
	//info_pos.y += 64 / 3;
	title.setPosition(info_pos);
	title.setString(string);
	title.setColor(sf::Color::Yellow);
	_info_table_sprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
	window.PrintString(title);
	window.Draw(_info_table_sprite);
	
	//time
	
	_itoa_s(
		(int)window.GetTime().asSeconds() - _gameStartTime,
		number_string,
		8, 10
	);
	string.clear();
	string += number_string;
	string += " sec";
	title.setString(string);
	timer_pos.x -= title.getGlobalBounds().width + 10;
	title.setPosition(timer_pos);
	title.setColor(sf::Color::White);
	window.PrintString(title);

}

void Player::Reset(Game::Position const & spawn_point, float gameStartTime)
{
	if (gameStartTime < 0)
		throw std::logic_error("negative time");
	_lives = 0;
	_coins = 0;
	
	//_spawn_points.push_back(Game::Position(Game::CoordType::Pixel, 1500, 300));
	_body->SetTransform(b2Vec2(0, 0), 0);
	_flags.win = false;
	_active_spawn_point = 0;
	_spawn_points.clear();
	_spawn_points.push_back(spawn_point);
	_body->SetTransform(b2Vec2(spawn_point.GetPhysicsPos().x, spawn_point.GetPhysicsPos().y), 0);
	_gameStartTime = gameStartTime;
}

bool Player::isWin()
{
	return _flags.win;
}

void Player::LastScreen(Game::Window & window)
{

	sf::Vector2f pos(
		window.GetCameraLeftTopPosition().GetPixelPos().x + window.GetSize().GetX() / 2,
		window.GetCameraLeftTopPosition().GetPixelPos().y + window.GetSize().GetY() / 4
	);
	sf::String string;
	sf::Text text = sf::Text();
	text.setFont(_font);
	text.setCharacterSize(50);
	char buff[8];

	if (_flags.win == false)
	{
		string += "Defeat";
		text.setString(string);
		text.setStyle(sf::Text::Regular);
		text.setColor(sf::Color(sf::Color::Red));
		pos.x -= text.getGlobalBounds().width / 2;
		text.setPosition(pos);
		window.PrintString(text);
	}
	else
	{
		string += "Victory";
		text.setString(string);
		text.setStyle(sf::Text::Regular);
		text.setColor(sf::Color(sf::Color::Cyan));
		pos.x -= text.getGlobalBounds().width / 2;
		text.setPosition(pos);
		window.PrintString(text);
	}

	text.setCharacterSize(35);
	text.setStyle(sf::Text::Italic);
	_itoa_s(_lives, buff, 8, 10);
	string = "Hearts: ";
	string += buff;
	pos.y += 70;
	text.setColor(sf::Color::Red);
	text.setPosition(pos);
	text.setString(string);
	window.PrintString(text);

	_itoa_s(_coins, buff, 8, 10);
	string = "Coins: ";
	string += buff;
	pos.y += 40;
	text.setColor(sf::Color::Yellow);
	text.setPosition(pos);
	text.setString(string);
	window.PrintString(text);

	_itoa_s(_flags.gameLength, buff, 8, 10);
	string = "Time: ";
	string += buff;
	string += " sec";
	pos.y += 40;
	text.setColor(sf::Color::White);
	text.setPosition(pos);
	text.setString(string);
	window.PrintString(text);

}

void Player::AddSpawnPoints(std::initializer_list<Game::Position> positions)
{
	for (auto iterator = positions.begin(); iterator != positions.end(); iterator++)
	{
		_spawn_points.push_back(*iterator);
	}
}

bool Player::update(Game::Window & window)
{
	if (CollisionCheck(window) == false)
	{
		b2Vec2 vec = _spawn_points[_active_spawn_point].GetPhysicsPos();
		_body->SetTransform(vec, 0);
		_body->SetLinearVelocity(b2Vec2(0, 0));
		_body->SetAngularVelocity(0);
		return false;
	}
	static Game::KEYBOARD_ACTION last_action = Game::KEYBOARD_ACTION::Inaction;
	switch (window.GetKeyboardAction())
	{
	case Game::KEYBOARD_ACTION::Right:
		if (_flags.in_the_air == false)
		{
			_body->ApplyForceToCenter(b2Vec2(50.f, 0.f), true);
			_animation_pack.SetActive("walk");
		}
		else
		{
			_body->ApplyForceToCenter(b2Vec2(5.f, 0.f), true);
		}
		_flags.flip = false;

		break;
	case Game::KEYBOARD_ACTION::Inaction:
		if (last_action == Game::KEYBOARD_ACTION::Right || last_action == Game::KEYBOARD_ACTION::Left)
		{
			if (_flags.in_the_air == false)
			{
				_body->SetLinearVelocity(b2Vec2(0, 0));
				_animation_pack.SetActive("stay");
			}
		}
		else if (_flags.in_the_air == false)
			_animation_pack.SetActive("stay");
		else if (last_action == Game::KEYBOARD_ACTION::Right || last_action == Game::KEYBOARD_ACTION::Left)
			_animation_pack.SetActive("stay");
		break;
	case Game::KEYBOARD_ACTION::Left:
		if (_flags.in_the_air == false)
		{
			_body->ApplyForceToCenter(b2Vec2(-50.f, 0.f), true);
			_animation_pack.SetActive("walk");
		}
		else
		{
			_body->ApplyForceToCenter(b2Vec2(-5.f, 0.f), true);
		}
		_flags.flip = true;

		break;
	case Game::KEYBOARD_ACTION::Up:
	case Game::KEYBOARD_ACTION::Jump:
		if (_flags.in_the_air || last_action == Game::KEYBOARD_ACTION::Jump || window.GetTime().asSeconds() - _flags.jump_time.asSeconds() < 0.5f) {
			break;
		}
		_animation_pack.SetActive("jump");
		_animation_pack.Replay();
		window.PlaySound("jump");
		//_body->ApplyForceToCenter(b2Vec2(0.f, -1000.f), true);
		_body->ApplyLinearImpulse(b2Vec2(0.f, -14.f), _body->GetWorldCenter(), true);
		_flags.jump_time = window.GetTime();
		break;
	case Game::KEYBOARD_ACTION::Exit:
		if (_exitMenuClock.getElapsedTime().asSeconds() < 0.5f) {
			break;
		}
		
		GameMenu menu { window, 50, {"Continue", "Exit"}, 40 };
		window.DrawBackground();
		sf::Clock menuLaunchClock;
		switch (menu.GetInput(window))
		{
		case 0:
			_gameStartTime += menuLaunchClock.getElapsedTime().asSeconds();
			break;
		case 1:
		case -1:
			return false;
		case -2:
			break;
		}
		_exitMenuClock.restart();
		break;
	}

	
	last_action = window.GetKeyboardAction();
	/*switch (window.GetMouseAction())
	{

	}*/
	
	Game::Position body_pos(Game::CoordType::Physics, _body->GetPosition().x, _body->GetPosition().y);

	//moving the camera
	
	window.MoveCamera(
		body_pos.GetPixelPos().x - (window.GetSize().GetPixelPos().x / 2),
		body_pos.GetPixelPos().y - (window.GetSize().GetPixelPos().y / 2)
	);

	UpdateScreenInfo(window);
	draw(window, _flags.flip);
	return true;
}
