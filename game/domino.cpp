#include "domino.h"

core::domino::domino()
	: left(-1), right(-1), pos(0), direction(DIRECTION::FORWARD)
{ }

core::domino::domino(uint8_t left, uint8_t right)
	: left(left), right(right), pos(0), direction(DIRECTION::FORWARD)
{ }

bool core::domino::operator>(domino& other)
{
	if (this->left == this->right && other.left == other.right && this->left > other.left)
		return true;
	if (this->left == this->right && other.left != other.right)
		return true;
	if (this->left + this->right > other.left + other.right && other.left != other.right)
		return true;
	else if ((this->left + this->right == other.left + other.right) && std::max(this->left, this->right) > std::max(other.left, other.right))
		return true;
	else
		return false;
}

bool core::domino::operator<(domino& other)
{
	if (this->left == this->right && other.left == other.right && this->left < other.left)
		return true;
	if (this->left != this->right && other.left == other.right)
		return true;
	if (this->left + this->right < other.left + other.right)
		return true;
	else if ((this->left + this->right == other.left + other.right) && std::max(this->left, this->right) < std::max(other.left, other.right))
		return true;
	else
		return false;
}

//core::DIRECTION core::domino::is_movable(int val, core::DIRECTION side)
//{
//	if (val == this->left && side == DIRECTION::LEFT)
//		return DIRECTION::RIGHT;
//
//	if (val == this->right && side == DIRECTION::RIGHT)
//		return DIRECTION::RIGHT;
//
//	if (val == this->left && side == DIRECTION::RIGHT)
//		return DIRECTION::LEFT;
//
//	if (val == this->right && side == DIRECTION::LEFT)
//		return DIRECTION::LEFT;
//
//	return DIRECTION::NONE;
//}


//core::PosDir core::domino::is_movable(int left, int right)
//{
//	if (this->top == left)
//		return core::PosDir(core::DIRECTION::RIGHT, core::DIRECTION::LEFT);
//	else if (this->top == right)
//		return core::PosDir(core::DIRECTION::LEFT, core::DIRECTION::RIGHT);
//	else if (this->bottom == left)
//		return core::PosDir(core::DIRECTION::LEFT, core::DIRECTION::LEFT);
//	else if (this->bottom == right)
//		return core::PosDir(core::DIRECTION::RIGHT, core::DIRECTION::RIGHT);
//
//	return core::PosDir();
//}
//
//core::PosDir core::domino::is_movable(domino & d2)
//{
//	if (this->dir == core::DIRECTION::NONE)
//	{
//		return is_movable(d2.top, d2.bottom);
//	}
//
//	return core::PosDir();
//}
