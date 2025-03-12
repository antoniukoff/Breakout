#include "math/vec3.h"
#include <cmath>

vec3 vec3::operator*(float scalar)
{
	return{ x * scalar, y * scalar, z * scalar };
}

vec3 vec3::operator*(const vec3& other)
{
	return{ x * other.x, y * other.y, z * other.z };
}

vec3 vec3::operator+(const vec3& other)
{
	return{ x + other.x, y + other.y, z + other.z };
}

void vec3::operator+=(const vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

vec3 vec3::operator-(const vec3& other) const
{
	return { x - other.x, y - other.y, z - other.z };
}

void vec3::operator-=(const vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

vec3 vec3::operator-(const vec3& other)
{
	return{ x - other.x, y - other.y, z - other.z };
}

vec3 vec3::operator-() const
{
	return { -x, -y, -z };
}

vec3 vec3::cross(const vec3& left, const vec3& right)
{
	vec3 crossed;
	crossed.x = left.y * right.z - left.z * right.y;
	crossed.y = left.z * right.x - left.x * right.z;
	crossed.z = left.x * right.y - left.y * right.x;

	return crossed;
}

float vec3::mag() const
{
	return sqrtf(x * x + y * y + z * z);
}

vec4 vec3::to_vec4() const
{
	return { x, y, z, 1.0f };
}

vec3 vec3::normalize(const vec3& vec)
{
	float mag = vec.mag();
	return { vec.x / mag, vec.y / mag, vec.z / mag };
}

float vec3::dot(const vec3& left, const vec3& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}
