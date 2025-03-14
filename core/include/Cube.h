#pragma once

#include "math/vec3.h"
#include <vector>

static const float cube_size = 3.0f;

/// Normals
static const vec3 forward_dir = { 0.0f , 0.0f, -1.0f };
static const vec3 back_dir = { 0.0f , 0.0f,  1.0f };
static const vec3 left_dir = { -1.0f , 0.0f,  0.0f };
static const vec3 right_dir = { 1.0f , 0.0f,  0.0f };
static const vec3 up_dir = { 0.0f , 1.0f,  0.0f };
static const vec3 down_dir = { 0.0f ,-1.0f,  0.0f };

inline std::vector<float> get_cube()
{
	return
	{
		/// FRONT
	-cube_size, -cube_size, cube_size, 0.0f, 0.0f, back_dir.x, back_dir.y, back_dir.z,
	 cube_size, -cube_size, cube_size, 1.0f, 0.0f, back_dir.x, back_dir.y, back_dir.z,
	 cube_size,  cube_size, cube_size, 1.0f, 1.0f, back_dir.x, back_dir.y, back_dir.z,

	 cube_size,  cube_size, cube_size, 1.0f, 1.0f, back_dir.x, back_dir.y, back_dir.z,
	-cube_size,  cube_size, cube_size, 0.0f, 1.0f, back_dir.x, back_dir.y, back_dir.z,
	-cube_size,	-cube_size, cube_size, 0.0f, 0.0f, back_dir.x, back_dir.y, back_dir.z,

	/// RIGHT
	cube_size, -cube_size,  cube_size, 0.0f, 0.0f, right_dir.x, right_dir.y, right_dir.z,
	cube_size, -cube_size, -cube_size, 1.0f, 0.0f, right_dir.x, right_dir.y, right_dir.z,
	cube_size,  cube_size, -cube_size, 1.0f, 1.0f, right_dir.x, right_dir.y, right_dir.z,

	cube_size,  cube_size, -cube_size, 1.0f, 1.0f, right_dir.x, right_dir.y, right_dir.z,
	cube_size,  cube_size,  cube_size, 0.0f, 1.0f, right_dir.x, right_dir.y, right_dir.z,
	cube_size, -cube_size,  cube_size, 0.0f, 0.0f, right_dir.x, right_dir.y, right_dir.z,

	/// LEFT
	-cube_size, -cube_size, -cube_size, 0.0f, 0.0f, left_dir.x, left_dir.y, left_dir.z,
	-cube_size, -cube_size,  cube_size, 1.0f, 0.0f, left_dir.x, left_dir.y, left_dir.z,
	-cube_size,  cube_size,  cube_size, 1.0f, 1.0f, left_dir.x, left_dir.y, left_dir.z,

	-cube_size,  cube_size,  cube_size, 1.0f, 1.0f, left_dir.x, left_dir.y, left_dir.z,
	-cube_size,  cube_size, -cube_size, 0.0f, 1.0f, left_dir.x, left_dir.y, left_dir.z,
	-cube_size, -cube_size, -cube_size, 0.0f, 0.0f, left_dir.x, left_dir.y, left_dir.z,

	/// TOP
	-cube_size, cube_size,  cube_size, 0.0f, 0.0f, up_dir.x, up_dir.y, up_dir.z,
	 cube_size, cube_size,  cube_size, 1.0f, 0.0f, up_dir.x, up_dir.y, up_dir.z,
	 cube_size, cube_size, -cube_size, 1.0f, 1.0f, up_dir.x, up_dir.y, up_dir.z,

	 cube_size, cube_size, -cube_size, 1.0f, 1.0f, up_dir.x, up_dir.y, up_dir.z,
	-cube_size, cube_size, -cube_size, 0.0f, 1.0f, up_dir.x, up_dir.y, up_dir.z,
	-cube_size, cube_size,  cube_size, 0.0f, 0.0f, up_dir.x, up_dir.y, up_dir.z,

	/// BOTTOM
   -cube_size, -cube_size, -cube_size, 0.0f, 0.0f, down_dir.x, down_dir.y, down_dir.z,
    cube_size, -cube_size, -cube_size, 1.0f, 0.0f, down_dir.x, down_dir.y, down_dir.z,
    cube_size, -cube_size,  cube_size, 1.0f, 1.0f, down_dir.x, down_dir.y, down_dir.z,

	cube_size, -cube_size,  cube_size, 1.0f, 1.0f, down_dir.x, down_dir.y, down_dir.z,
   -cube_size, -cube_size,  cube_size, 0.0f, 1.0f, down_dir.x, down_dir.y, down_dir.z,
   -cube_size, -cube_size, -cube_size, 0.0f, 0.0f, down_dir.x, down_dir.y, down_dir.z,

   /// BACK
    cube_size, -cube_size, -cube_size, 0.0f, 0.0f, forward_dir.x, forward_dir.y, forward_dir.z,
   -cube_size, -cube_size, -cube_size, 1.0f, 0.0f, forward_dir.x, forward_dir.y, forward_dir.z,
   -cube_size,  cube_size, -cube_size, 1.0f, 1.0f, forward_dir.x, forward_dir.y, forward_dir.z,

   -cube_size,  cube_size, -cube_size, 1.0f, 1.0f, forward_dir.x, forward_dir.y, forward_dir.z,
    cube_size,  cube_size, -cube_size, 0.0f, 1.0f, forward_dir.x, forward_dir.y, forward_dir.z,
    cube_size, -cube_size, -cube_size, 0.0f, 0.0f, forward_dir.x, forward_dir.y, forward_dir.z,
	};
}



