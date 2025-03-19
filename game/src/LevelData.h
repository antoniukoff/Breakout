#pragma once 
#include <vector>
#include <math/vec3.h>

const float z_depth = -40.0f;

const vec3 arena_scale           = vec3{ 85, 45.0f, 1.0f };
const vec3 horizontal_wall_scale = vec3{ 1.0f, arena_scale.y, 1.0f };
const vec3 vertical_wall_scale   = vec3{ arena_scale.x, 1.0f, 1.0f };
const vec3 paddle_scale          = vec3{ 10.0f, 2.0f, 1.0f };
const vec3 ball_scale			 = vec3{};
const vec3 brick_scale			 = vec3{5.0f, 2.5, 1.0f};

enum ObjectType
{
	BACK_WALL_ARENA = -3,
	HORIZONTAL_WALL,
	VERTICAL_WALL,
	EMPTY,
	BALL,
	PADDLE,
	BRICK,
	SOLID_BRICK,
};

inline const std::vector<std::vector<std::vector<int> > > g_levels =
{
	{
		{0,3,3,3,0},
		{0,3,3,3,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,1,0,0},
		{0,0,2,0,0}
	},

	{
		{3, 3, 3, 3, 3, 4, 3},
		{3, 3, 4, 3, 3, 3, 3},
		{3, 3, 3, 4, 3, 3, 3},
		{3, 3, 3, 3, 3, 3, 3},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 2, 0, 0, 0},
	},

	{
		{3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3},
		{3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3},
		{3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3},
		{3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
	}
};