#pragma once

#include <list>
#include <map>
#include <vector>
#include "board.h"
#include "domino.h"

namespace core
{
	class board;

	class player
	{
	public:
		std::list<domino*> sticks;
		int id;

		void move();
		void push_stick(domino* pstick);
		void remove_stick(domino* pstick);
		domino* get_max();
		//std::vector<domino> get_movables(DIRECTION side, int val);
		std::map<domino*, domino> get_movables(DIRECTION side, int val);
		std::vector<std::pair<domino*, domino>> get_movables(core::board board);

		player();
		player(int id);

	private:
		//domino* getmax();
	};
}