#pragma once


#include "domino.h"
#include "player.h"
#include <ctime>
#include <vector>
#include <list>


// default: two players offline



namespace core
{
	class player;

	class board
	{
	public:

		board();
		board(size_t types_count, size_t countOfSticksForOnePlayer);
		
		void generate_layout();
		

		size_t types_count;
		size_t one_player_sticks_count;

		uint8_t right;
		uint8_t left;

		std::vector<domino*> all_sticks;
		std::vector<domino*> onboard_sticks;
		//core::player player1;
		//core::player player2;

		std::vector<core::player*> players;

		bool brute_moves(core::board board, std::vector<core::player*> _players, std::list<std::pair<int, core::domino>>& moves);

		//std::list<domino*> player1;
		//std::list<domino*> player2;

		//std::list<Player> players;
		uint8_t get_right_pos();
		uint8_t get_left_pos();

	private:

		uint8_t right_pos = 0;
		uint8_t left_pos = 0;

		void place_stick(domino* pstick, DIRECTION side, DIRECTION dir);
		void place_stick(domino* pstick, DIRECTION side);
		void place_stick(domino* pstick);
		void place_left(domino* pstick);
		void place_right(domino* pstick);
	};
}