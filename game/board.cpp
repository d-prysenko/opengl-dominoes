#include "board.h"



core::board::board()
	: types_count(0), one_player_sticks_count(0)
{
}

core::board::board(size_t types_count, size_t one_player_sticks_count)
	: types_count(types_count), one_player_sticks_count(one_player_sticks_count)
{
	srand(time(0));

	players.push_back(new core::player());
	players.push_back(new core::player());
	
	for (int i = 0; i < types_count; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			all_sticks.push_back(new domino(i, j));
		}
	}

	int sticks_count = all_sticks.size();

	// Shuffle the dominoes
	for (size_t i = 0; i < sticks_count; i++)
	{
		std::swap(all_sticks[rand() % sticks_count], all_sticks[rand() % sticks_count]);
	}

	for (int i = 0; i < one_player_sticks_count; i++)
	{
		players[0]->push_stick(all_sticks.back()); all_sticks.pop_back();
		players[1]->push_stick(all_sticks.back()); all_sticks.pop_back();
	}

	for (auto s = players[0]->sticks.begin(); s != players[0]->sticks.end(); s++)
	{
		printf("%d|%d  ", (*s)->left, (*s)->right);
	}

	printf("\n");

	for (auto s = players[1]->sticks.begin(); s != players[1]->sticks.end(); s++)
	{
		printf("%d|%d  ", (*s)->left, (*s)->right);
	}

	printf("\n");

	domino* max1 = players[0]->get_max();
	domino* max2 = players[1]->get_max();

	//if (*max1 > *max2)
	{
		printf("Player 1 open the game with stick %d|%d\n", max1->left, max1->right);
		place_stick(max1);
		players[0]->remove_stick(max1);
	}
	//else
	//{
	//	printf("Player 2 open the game with stick %d|%d\n", max2->left, max2->right);
	//	place_stick(max2);
	//	players[1]->remove_stick(max2);
	//}

	std::list<std::pair<int, core::domino>> moves;

	if (brute_moves(*this, players, moves))
	{
		printf("YYYEEEEEAAAAAHHHHH!!\n");
	}
	else
	{
		printf("no:(\n");
	}

	//auto p1l = player1.get_movables(DIRECTION::LEFT, left);
	//auto p1r = player1.get_movables(DIRECTION::RIGHT, right);

	//for (auto move_stick : p1l)
	//{
	//	player1.place_stick(_board, move_stick);
	//	player2.place_stick(_board, move_stick);
	//}

}


bool core::board::brute_moves(core::board board, std::vector<core::player*> players, std::list<std::pair<int, core::domino>>& moves)
{
	static uint8_t player_id = 1;
	auto movables = players[player_id]->get_movables(board);
	if (players[player_id]->sticks.size() == 0)
		return false;
	if (movables.size() == 0 && player_id == 1)
		return true;

	for (auto stick : movables)
	{
		//place_stick(stick);
		//std::list<std::pair<int, core::domino>> _moves;
		std::vector<core::player*> _players = players;
		board.place_stick(&stick.second);
		_players[player_id]->remove_stick(stick.first);
		//_moves.push_back(std::pair<int, core::domino>(player_id, stick.second));
		int last_pl_id = player_id;
		player_id = (player_id + 1) % 2;
		bool res = brute_moves(board, _players, moves);
		if (res)
		{
			//auto last = moves.back();
			//moves = _moves;
			//moves.push_front(last);
			moves.push_front(std::pair<int, core::domino>(last_pl_id, stick.second));
			return true;
		}
		player_id = last_pl_id;
	}
	return false;
}

uint8_t core::board::get_right_pos()
{
	return right_pos;
}

uint8_t core::board::get_left_pos()
{
	return left_pos;
}

//void core::board::place_stick(domino* pstick, DIRECTION side)
//{
//	if (onboard_sticks.size() == 0)
//	{
//		right = pstick->right;
//		left = pstick->left;
//		onboard_sticks.push_back(pstick);
//	}
//
//	if (side == DIRECTION::LEFT)
//	{
//		if (pstick->direction == DIRECTION::NONE)
//			left = pstick->left;
//		else
//			left = pstick->right;
//
//		pstick->pos = --left_pos;
//		onboard_sticks.push_back(pstick);
//	}
//}

void core::board::place_stick(domino* pstick)
{	
	if (pstick->pos > 0)
		place_right(pstick);
	else if(pstick->pos < 0)
		place_left(pstick);
	else
	{
		onboard_sticks.push_back(pstick);
		left = pstick->left;
		right = pstick->right;
	}
}

void core::board::place_left(domino* pstick)
{
	onboard_sticks.push_back(pstick);
	left_pos++;
	if (pstick->direction == DIRECTION::FORWARD)
	{
		left = pstick->left;
	}
	else
	{
		left = pstick->right;
	}
}

void core::board::place_right(domino* pstick)
{
	onboard_sticks.push_back(pstick);
	right_pos++;
	if (pstick->direction == DIRECTION::FORWARD)
	{
		right = pstick->right;
	}
	else
	{
		right = pstick->left;
	}
}
