#pragma once

#include <inttypes.h>
#include <algorithm>

namespace core
{
	enum class DIRECTION : uint8_t
	{
		NONE = 1,
		FORWARD,
		BACKWARD
	};

	class domino
	{
	public:
		uint8_t left;
		uint8_t right;

		int8_t pos;

		//PosDir dir;
		DIRECTION direction;

		/*
		0, if not belongs to anyone
		n, if belongs to n player
		*/
		//int8_t relation;



		domino();
		domino(uint8_t left, uint8_t right);

		bool operator>(domino& right);
		bool operator<(domino& right);

		//DIRECTION is_movable(int val, DIRECTION dir);
	};

}