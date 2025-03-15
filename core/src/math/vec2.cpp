#include "math/vec2.h"

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
