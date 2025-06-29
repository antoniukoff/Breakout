#pragma once
#include <random>
#include "vec3.h"
#include "vec2.h"
#include "../color.h"

class random
{
public:
	inline static float get_random_float(float min, float max)
	{
		static std::mt19937 random_engine(time(nullptr));
		std::uniform_real_distribution<float> distrib(min, max);

		return distrib(random_engine);
	}

	inline static color get_random_color()
	{
		unsigned char r = (unsigned char)random::get_random_float(0, 255);
		unsigned char g = (unsigned char)random::get_random_float(0, 255);
		unsigned char b = (unsigned char)random::get_random_float(0, 255);

		return color{ r, g, b, 255 };
	}
};