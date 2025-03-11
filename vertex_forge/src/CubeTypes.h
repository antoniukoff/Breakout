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

inline const vec3 forward_dir	= {  0.0f , 0.0f, -1.0f };
inline const vec3 back_dir		= {  0.0f , 0.0f,  1.0f };
inline const vec3 left_dir		= { -1.0f , 0.0f,  0.0f };
inline const vec3 right_dir		= {	 1.0f , 0.0f,  0.0f };
inline const vec3 up_dir		= {	 0.0f , 1.0f,  0.0f };
inline const vec3 down_dir		= {	 0.0f ,-1.0f,  0.0f };

	
inline std::vector<float> get_cube_with_normals()	
{	
	return	
	{	
		/// FRONT
	-cube_size, -cube_size, cube_size, back_dir.x, back_dir.y, back_dir.z,
	 cube_size, -cube_size, cube_size, back_dir.x, back_dir.y, back_dir.z,
	 cube_size,  cube_size, cube_size, back_dir.x, back_dir.y, back_dir.z,

	 cube_size,  cube_size, cube_size, back_dir.x, back_dir.y, back_dir.z,
	-cube_size,  cube_size, cube_size, back_dir.x, back_dir.y, back_dir.z,
	-cube_size,	-cube_size, cube_size, back_dir.x, back_dir.y, back_dir.z,

	/// RIGHT
	cube_size, -cube_size,  cube_size, right_dir.x, right_dir.y, right_dir.z,
	cube_size, -cube_size, -cube_size, right_dir.x, right_dir.y, right_dir.z,
	cube_size,  cube_size, -cube_size, right_dir.x, right_dir.y, right_dir.z,

	cube_size,  cube_size, -cube_size, right_dir.x, right_dir.y, right_dir.z,
	cube_size,  cube_size,  cube_size, right_dir.x, right_dir.y, right_dir.z,
	cube_size, -cube_size,  cube_size, right_dir.x, right_dir.y, right_dir.z,

	/// LEFT
	-cube_size, -cube_size, -cube_size, left_dir.x, left_dir.y, left_dir.z,
	-cube_size, -cube_size,  cube_size, left_dir.x, left_dir.y, left_dir.z,
	-cube_size,  cube_size,  cube_size, left_dir.x, left_dir.y, left_dir.z,

	-cube_size,  cube_size,  cube_size, left_dir.x, left_dir.y, left_dir.z,
	-cube_size,  cube_size, -cube_size, left_dir.x, left_dir.y, left_dir.z,
	-cube_size, -cube_size, -cube_size, left_dir.x, left_dir.y, left_dir.z,

	/// TOP
	-cube_size, cube_size,  cube_size, up_dir.x, up_dir.y, up_dir.z,
	 cube_size, cube_size,  cube_size, up_dir.x, up_dir.y, up_dir.z,
	 cube_size, cube_size, -cube_size, up_dir.x, up_dir.y, up_dir.z,

	 cube_size, cube_size, -cube_size, up_dir.x, up_dir.y, up_dir.z,
	-cube_size, cube_size, -cube_size, up_dir.x, up_dir.y, up_dir.z,
	-cube_size, cube_size,  cube_size, up_dir.x, up_dir.y, up_dir.z,

	/// BOTTOM
   -cube_size, -cube_size, -cube_size, down_dir.x, down_dir.y, down_dir.z,
	cube_size, -cube_size, -cube_size, down_dir.x, down_dir.y, down_dir.z,
	cube_size, -cube_size,  cube_size, down_dir.x, down_dir.y, down_dir.z,

	cube_size, -cube_size,  cube_size, down_dir.x, down_dir.y, down_dir.z,
   -cube_size, -cube_size,  cube_size, down_dir.x, down_dir.y, down_dir.z,
   -cube_size, -cube_size, -cube_size, down_dir.x, down_dir.y, down_dir.z,

   /// BACK
	cube_size, -cube_size, -cube_size, forward_dir.x, forward_dir.y, forward_dir.z,
   -cube_size, -cube_size, -cube_size, forward_dir.x, forward_dir.y, forward_dir.z,
   -cube_size,  cube_size, -cube_size, forward_dir.x, forward_dir.y, forward_dir.z,

   -cube_size,  cube_size, -cube_size, forward_dir.x, forward_dir.y, forward_dir.z,
	cube_size,  cube_size, -cube_size, forward_dir.x, forward_dir.y, forward_dir.z,
	cube_size, -cube_size, -cube_size, forward_dir.x, forward_dir.y, forward_dir.z,
	};
}
