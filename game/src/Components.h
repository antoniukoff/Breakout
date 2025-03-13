#pragma once
#include <	utility.h>

struct Transform
{
	float x;
	float y;
};

ANNOTATE(
Transform,
	2, 
	DEFINE_COMPONENT_MEMBER(Transform, 0, float, x)
	DEFINE_COMPONENT_MEMBER(Transform, 1, float, y)
)

DEFINE_COMPONENT_HANDLE(Transform,
	COMPONENT_HANDLE_ACCESSOR(0, float, x)
	COMPONENT_HANDLE_ACCESSOR(1, float, y)
)