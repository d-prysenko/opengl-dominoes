#pragma once


#include <inttypes.h>
#include <set>
#include <list>
#include <vector>
#include <ctime>
#include "domino.h"
#include "board.h"

namespace core
{

	class Logic
	{
	public:
		//std::list<domino*> board;
		//std::list<domino*>::iterator root;

		//std::list<domino*> board_left;
		//domino* board_start;
		//std::list<domino*> board_right;

		board board;

		std::vector<domino*> all_sticks;
		
		// online
		Logic();

		// offline
		Logic(size_t types_count, size_t one_player_sticks_count);

		//void generate_layout();

		static void update();
	private:
		//board board;


	};

}