#include "logic.h"

core::Logic::Logic()
{
	printf("There is no online mode yet\n");
}

core::Logic::Logic(size_t types_count, size_t one_player_sticks_count)
	: board(types_count, one_player_sticks_count)
{
	

	//generate_layout();
}

void get_movable_stick()
{

}

//
//void engine::dominoes::generate_layout()
//{
//	size_t sticksCount = heap.size();
//	size_t sticksOnBoard = sticksCount - 2 * countOfSticksForOnePlayer;
//
//	printf("%d will be placed on board\n", sticksOnBoard);
//
//	srand(time(0));
//
//	for (size_t i = 0; i < sticksCount; i++)
//	{
//		std::swap(heap[rand() % sticksCount], heap[rand() % sticksCount]);
//	}
//
//	player_init(player1);
//	player_init(player2);
//
//	printf("First Player sticks:\n");
//	player_print_sticks(player1);
//
//	printf("Second Player sticks:\n");
//	player_print_sticks(player2);
//
//	auto stick = heap.back(); heap.pop_back();
//	board_start = stick;
//
//	for (int i = 0; i < (sticksOnBoard-1)/2; i++)
//	{
//		auto stick = heap.back(); heap.pop_back();
//		stick->relation = 1 + rand() % 2;
//		board_left.push_back(stick);
//	}
//
//	for (int i = 0; i < (sticksOnBoard - 1) / 2; i++)
//	{
//		auto stick = heap.back(); heap.pop_back();
//		stick->relation = 1 + rand() % 2;
//		board_right.push_back(stick);
//	}
//
//	printf("%d %d\n", board_start->top, board_start->bottom);
//
//}
//
//void engine::dominoes::player_init(std::list<engine::domino*>& pl)
//{
//	for (size_t i = 0; i < countOfSticksForOnePlayer; i++)
//	{
//		auto stick = heap.back(); heap.pop_back();
//		pl.push_back(stick);
//	}
//}
//
//void engine::dominoes::player_print_sticks(std::list<engine::domino*>& pl)
//{
//	auto it = pl.begin();
//	for (int i = 0; i < countOfSticksForOnePlayer; it++, i++)
//	{
//		printf("%d ", (*it)->top);
//	}
//	printf("\n");
//	for (size_t i = 0; i < countOfSticksForOnePlayer; i++)
//	{
//		printf("- ");
//	}
//	printf("\n");
//	it = pl.begin();
//	for (size_t i = 0; i < countOfSticksForOnePlayer; it++, i++)
//	{
//		printf("%d ", (*it)->bottom);
//	}
//	printf("\n\n");
//}



void core::Logic::update()
{
}


//
//void engine::dominoes::player1move()
//{
//	move(player1);
//}
//
//void engine::dominoes::player2move()
//{
//	move(player2);
//}
//
//void engine::dominoes::refresh_stick_state(std::list<domino*>& player)
//{
//	for (auto it = player.begin(); it != player.end(); it++)
//	{
//		if ((*it)->bottom == left || (*it)->top == left)
//		{
//			(*it)->isPlayable = engine::left;
//		}
//		if ((*it)->bottom == right || (*it)->top == right)
//		{
//			if ((*it)->isPlayable == engine::left)
//			{
//				(*it)->isPlayable = engine::both;
//			}
//			else
//			{
//				(*it)->isPlayable = engine::right;
//			}
//		}
//		else
//		{
//			(*it)->isPlayable = engine::none;
//		}
//	}
//}
//
//engine::domino* engine::dominoes::getmax(std::list<domino*> sticks)
//{
//	size_t size = sticks.size();
//
//	engine::domino* dbl = nullptr;
//	engine::domino* other = nullptr;
//
//	for (auto it = sticks.begin(); it != sticks.end(); ++it)
//	{
//		if ((*it)->top == (*it)->bottom && (dbl == nullptr || (*it)->top > dbl->top))
//		{
//			dbl = *it;
//		}
//		else if (other == nullptr || (*it)->top + (*it)->bottom > other->top + other->bottom)
//		{
//			other = *it;
//		}
//	}
//
//	if (dbl != nullptr)
//		return dbl;
//	else
//		return other;
//}