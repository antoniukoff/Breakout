#pragma once
#include <vector>

inline static float cube_size = 3.0f;

inline std::vector<float> get_textured_cube()
{
	return
	{
		/// FRONT
	-cube_size, -cube_size, cube_size, 0.0f, 0.0f, 1.0f,
	 cube_size, -cube_size, cube_size, 1.0f, 0.0f, 1.0f,
	 cube_size,  cube_size, cube_size, 1.0f, 1.0f, 1.0f,

	 cube_size,  cube_size, cube_size, 1.0f, 1.0f, 1.0f,
	-cube_size,  cube_size, cube_size, 0.0f, 1.0f, 1.0f,
	-cube_size,	-cube_size, cube_size, 0.0f, 0.0f, 1.0f,

	/// RIGHT
	cube_size, -cube_size,  cube_size, 0.0f, 0.0f, 1.0f,
	cube_size, -cube_size, -cube_size, 1.0f, 0.0f, 1.0f,
	cube_size,  cube_size, -cube_size, 1.0f, 1.0f, 1.0f,

	cube_size,  cube_size, -cube_size, 1.0f, 1.0f, 1.0f,
	cube_size,  cube_size,  cube_size, 0.0f, 1.0f, 1.0f,
	cube_size, -cube_size,  cube_size, 0.0f, 0.0f, 1.0f,

	/// LEFT
	-cube_size, -cube_size, -cube_size, 0.0f, 0.0f, 1.0f,
	-cube_size, -cube_size,  cube_size, 1.0f, 0.0f, 1.0f,
	-cube_size,  cube_size,  cube_size, 1.0f, 1.0f, 1.0f,

	-cube_size,  cube_size,  cube_size, 1.0f, 1.0f, 1.0f,
	-cube_size,  cube_size, -cube_size, 0.0f, 1.0f, 1.0f,
	-cube_size, -cube_size, -cube_size, 0.0f, 0.0f, 1.0f,

	/// TOP
	-cube_size, cube_size,  cube_size, 0.0f, 0.0f, 1.0f,
	 cube_size, cube_size,  cube_size, 1.0f, 0.0f, 1.0f,
	 cube_size, cube_size, -cube_size, 1.0f, 1.0f, 1.0f,

	 cube_size, cube_size, -cube_size, 1.0f, 1.0f, 1.0f,
	-cube_size, cube_size, -cube_size, 0.0f, 1.0f, 1.0f,
	-cube_size, cube_size,  cube_size, 0.0f, 0.0f, 1.0f,

	/// BOTTOM
   -cube_size, -cube_size, -cube_size, 0.0f, 0.0f, 1.0f,
    cube_size, -cube_size, -cube_size, 1.0f, 0.0f, 1.0f,
    cube_size, -cube_size,  cube_size, 1.0f, 1.0f, 1.0f,

	cube_size, -cube_size,  cube_size, 1.0f, 1.0f, 1.0f,
   -cube_size, -cube_size,  cube_size, 0.0f, 1.0f, 1.0f,
   -cube_size, -cube_size, -cube_size, 0.0f, 0.0f, 1.0f,

   /// BACK
    cube_size, -cube_size, -cube_size, 0.0f, 0.0f, 1.0f,
   -cube_size, -cube_size, -cube_size, 1.0f, 0.0f, 1.0f,
   -cube_size,  cube_size, -cube_size, 1.0f, 1.0f, 1.0f,

   -cube_size,  cube_size, -cube_size, 1.0f, 1.0f, 1.0f,
    cube_size,  cube_size, -cube_size, 0.0f, 1.0f, 1.0f,
    cube_size, -cube_size, -cube_size, 0.0f, 0.0f, 1.0f
	};
}

inline std::vector<float> get_default_cube()
{
	return
	{
		/// FRONT
	-cube_size, -cube_size, cube_size,
	 cube_size, -cube_size, cube_size,
	 cube_size,  cube_size, cube_size,

	 cube_size,  cube_size, cube_size,
	-cube_size,  cube_size, cube_size,
	-cube_size,	-cube_size, cube_size,

	/// RIGHT
	cube_size, -cube_size,  cube_size,
	cube_size, -cube_size, -cube_size,
	cube_size,  cube_size, -cube_size,

	cube_size,  cube_size, -cube_size,
	cube_size,  cube_size,  cube_size,
	cube_size, -cube_size,  cube_size,

	/// LEFT
	-cube_size, -cube_size, -cube_size,
	-cube_size, -cube_size,  cube_size,
	-cube_size,  cube_size,  cube_size,

	-cube_size,  cube_size,  cube_size,
	-cube_size,  cube_size, -cube_size,
	-cube_size, -cube_size, -cube_size,

	/// TOP
	-cube_size, cube_size,  cube_size,
	 cube_size, cube_size,  cube_size,
	 cube_size, cube_size, -cube_size,

	 cube_size, cube_size, -cube_size,
	-cube_size, cube_size, -cube_size,
	-cube_size, cube_size,  cube_size,

	/// BOTTOM
   -cube_size, -cube_size, -cube_size,
	cube_size, -cube_size, -cube_size,
	cube_size, -cube_size,  cube_size,

	cube_size, -cube_size,  cube_size,
   -cube_size, -cube_size,  cube_size,
   -cube_size, -cube_size, -cube_size,

   /// BACK
	cube_size, -cube_size, -cube_size,
   -cube_size, -cube_size, -cube_size,
   -cube_size,  cube_size, -cube_size,

   -cube_size,  cube_size, -cube_size,
	cube_size,  cube_size, -cube_size,
	cube_size, -cube_size, -cube_size,
	};
}
