#include "player.h"

namespace core
{

	player::player()
		: id(0)
	{
	}

	player::player(int id)
		: id(id)
	{
	}

	void player::move()
	{
		//if (board.size() == 0)
		//{
		//	auto stick = getmax();
		//	printf("%d | %d\n", stick->top, stick->bottom);
		//	return;
		//}



	}

	void player::push_stick(domino* pstick)
	{
		sticks.push_back(pstick);
	}

	void player::remove_stick(domino* pstick)
	{
		sticks.remove(pstick);
	}

	domino* player::get_max()
	{
		if (sticks.size() == 0)
			return nullptr;

		domino* max = sticks.front();
		for (auto it = sticks.begin(); it != sticks.end(); it++)
		{
			if (**it > *max)
			{
				max = *it;
			}
		}

		return max;
	}

	//std::map<domino*, domino> player::get_movables(DIRECTION side, int val)
	//{
	//	std::map<domino*, domino> movables;

	//	for (domino* stick : sticks)
	//	{
	//		if (side == DIRECTION::LEFT && stick->right == val)
	//		{
	//			movables[stick] = *stick;
	//			movables[stick].direction = DIRECTION::NONE;
	//		}
	//		else if (side == DIRECTION::LEFT && stick->left == val)
	//		{
	//			movables[stick] = *stick;
	//			movables[stick].direction = DIRECTION::BACKWARD;
	//		}
	//		else if (side == DIRECTION::RIGHT && stick->right == val)
	//		{
	//			movables[stick] = *stick;
	//			movables[stick].direction = DIRECTION::BACKWARD;
	//		}
	//		else if (side == DIRECTION::RIGHT && stick->left == val)
	//		{
	//			movables[stick] = *stick;
	//			movables[stick].direction = DIRECTION::NONE;
	//		}
	//	}

	//	return movables;

	//}

	std::vector<std::pair<domino*, domino>> core::player::get_movables(core::board board)
	{
		std::vector<std::pair<domino*, domino>> movables;
		for (auto pstick : sticks)
		{
			if (board.right == pstick->left)
			{
				std::pair<domino*, domino> p(pstick, *pstick);
				p.second.direction = DIRECTION::FORWARD;
				p.second.pos = board.get_right_pos()+1;
				movables.push_back(p);
			}
			if (board.right == pstick->right)
			{
				std::pair<domino*, domino> p(pstick, *pstick);
				p.second.direction = DIRECTION::BACKWARD;
				p.second.pos = board.get_right_pos()+1;
				movables.push_back(p);
			}
			if (board.left == pstick->right)
			{
				std::pair<domino*, domino> p(pstick, *pstick);
				p.second.direction = DIRECTION::FORWARD;
				p.second.pos = -board.get_left_pos()-1;
				movables.push_back(p);
			}
			if (board.left == pstick->left)
			{
				std::pair<domino*, domino> p(pstick, *pstick);
				p.second.direction = DIRECTION::BACKWARD;
				p.second.pos = -board.get_left_pos()-1;
				movables.push_back(p);
			}
		}
		return movables;
	}

	//domino* player::getmax()
	//{
	//	size_t size = sticks.size();

	//	domino* dbl = nullptr;
	//	domino* other = nullptr;

	//	for (size_t i = 0; i < size; i++)
	//	{
	//		if (sticks[i]->left == sticks[i]->right && (dbl == nullptr || sticks[i]->left > dbl->left))
	//		{
	//			dbl = sticks[i];
	//		}
	//		else if (other == nullptr || sticks[i]->left + sticks[i]->right > other->left + other->right)
	//		{
	//			other = sticks[i];
	//		}
	//	}

	//	if (dbl != nullptr)
	//		return dbl;
	//	else
	//		return other;
	//}
}