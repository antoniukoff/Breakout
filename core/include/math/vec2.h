#pragma once

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

	float mag() const;
	static vec2 normalize(const vec2& vec);
	static float dot(const vec2& left, const vec2& right);
};
