#include "math/vec2.h"
#include <algorithm>

void vec2::operator+=(const vec2& other)
{
	x += other.x;
	y += other.y;
}

vec2 vec2::operator+(const vec2& other) const
{
	return { x + other.x, y + other.y };
}

vec2 vec2::operator*(float scalar) const
{
	return { x * scalar, y * scalar };
}

vec2 vec2::operator-() const
{
	return { -x, -y };
}

void vec2::operator-=(const vec2& other)
{
	x -= other.x;
	y -= other.y;
}

vec2 vec2::operator-(const vec2& other) const
{
	return { x - other.x, y - other.y };
}

vec2 vec2::operator/(const vec2& other) const
{
	return { x / other.x, y / other.y };

}

vec2 vec2::operator/(float scalar) const
{
	return { x / scalar, y / scalar };

}

vec3 vec2::to_vec3()
{
	return { x, y, 0.0f };
}

float vec2::mag() const
{
	return sqrtf(x * x + y * y);
}

vec2 vec2::normalize(const vec2& vec)
{
	float magnitude = vec.mag();
	return { vec.x / magnitude, vec.y / magnitude };
}

float vec2::dot(const vec2& left, const vec2& right)
{
	return left.x * right.x + left.y * right.y;
}

vec2 vec2::clamp(vec2 to_clamp, vec2 min, vec2 max)
{
	float x = std::clamp(to_clamp.x, min.x, max.x);
	float y = std::clamp(to_clamp.y, min.y, max.y);

	return { x, y };
}
