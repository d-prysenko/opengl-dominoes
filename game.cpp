#include "game.h"

core::Logic* logic;
core::Window* window;
core::Renderer* renderer;

Game::Game(Mode mode)
{
	if (mode & Mode::ONLINE)
	{
		// online constuctor which takes count of players
	}
	else
	{
		// offline
		logic = new core::Logic(DEFAULT_NUMBER_OF_STICK_TYPES, DEFAULT_NUMBER_OF_PLAYERS_STICKS_2);
	}
}

//Game::Game(size_t stickTypesCount, size_t countOfSticksForOnePlayer)
//{ 
//	logic = new core::Logic(stickTypesCount, countOfSticksForOnePlayer);
//}

void Game::window_create(int width, int height)
{
	window = new core::Window(width, height);
}

void Game::loop()
{
	init();

	while (!window->isWindowShuldClose)
	{
		update();
		render();
		end_scene();
	}
}

inline void Game::init()
{
	renderer = new core::Renderer();
}

inline void Game::update()
{
	//event e;
	//while (e = window.getevent())
	//{
	//	logic.update(e);
	//}
}

inline void Game::render()
{
	renderer->render();
}

inline void Game::end_scene()
{
	window->end_scene();
}