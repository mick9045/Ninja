#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "GameWorld.h"
#include "Menu.h"
#include <Windows.h>


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	GameWorld *world = new GameWorld("Ninja", 0.f, 9.8f);
	world->Launch();
	delete world;
	return 0;
}