#pragma once

static const float STICK_WIDTH = 0.5f;
static const float STICK_HEIGHT = 2 * STICK_WIDTH;

const float stick_h[] =
{
	 STICK_HEIGHT / 2,  STICK_WIDTH / 2,
	 STICK_HEIGHT / 2, -STICK_WIDTH / 2,
	-STICK_HEIGHT / 2, -STICK_WIDTH / 2,
	-STICK_HEIGHT / 2,  STICK_WIDTH / 2,
	 STICK_HEIGHT / 2,  STICK_WIDTH / 2,
	 0,					STICK_WIDTH / 2,
	 0,				   -STICK_WIDTH / 2
};

const float stick_v[] =
{
	 STICK_WIDTH / 2,  STICK_HEIGHT / 2,
	 STICK_WIDTH / 2, -STICK_HEIGHT / 2,
	-STICK_WIDTH / 2, -STICK_HEIGHT / 2,
	-STICK_WIDTH / 2,  STICK_HEIGHT / 2,
	 STICK_WIDTH / 2,  STICK_HEIGHT / 2,
	 STICK_WIDTH / 2,  0,
	-STICK_WIDTH / 2,  0
};

const float stick_color[] =
{
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
};

const float stick_dotes[][16] =
{
	// 1
	{
		0.0f, 0.0f
	},
	// 2
	{
		-STICK_WIDTH / 2, 0.0f,
		 STICK_WIDTH / 2, 0.0f
	},
	// 3
	{
		0.0f, 0.0f,
		-STICK_WIDTH / 2, 0.0f,
		 STICK_WIDTH / 2, 0.0f
	},
	// 4
	{
		0.0f, 0.0f,
		-STICK_WIDTH / 2, 0.0f,
		 STICK_WIDTH / 2, 0.0f
	}
};
