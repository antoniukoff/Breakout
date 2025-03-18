#pragma once
#include "vec3.h"

#include <cmath>

struct vec2
{
	float x = 0.0f;
	float y = 0.0f;

	vec2 operator -(const vec2& other) const;
	void operator +=(const vec2& other);
	void operator -=(const vec2& other);
	vec2 operator +(const vec2& other) const;
	vec2 operator *(float scalar) const;
	vec2 operator /(const vec2& other) const;
	vec2 operator /(float scalar) const;

	vec2 operator -() const;


	vec3 to_vec3();
	float mag() const;
	static vec2 normalize(const vec2& vec);
	static float dot(const vec2& left, const vec2& right);
	static vec2 clamp(vec2 to_clamp, vec2 min, vec2 max);

};
