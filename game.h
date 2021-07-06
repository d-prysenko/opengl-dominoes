#pragma once

#include "state.h"

#define DEFAULT_NUMBER_OF_STICK_TYPES 7
#define DEFAULT_NUMBER_OF_PLAYERS_STICKS_2 7
#define DEFAULT_NUMBER_OF_PLAYERS_STICKS_4 4


class Game
{
public:
	enum class Mode : uint8_t
	{
		OFFLINE = 0 << 0,
		ONLINE = 1 << 0,
		TWOPLAYERS = 0 << 1,
		FOURPLAYERS = 1 << 1
	};

	friend constexpr bool operator&(const enum Mode self, const enum Mode in)
	{
		return uint8_t(self) & uint8_t(in);
	}

	Game(Mode mode);

	void window_create(int width, int height);
	void loop();

private:
	inline void init();
	inline void update();
	inline void render();
	inline void end_scene();
};

