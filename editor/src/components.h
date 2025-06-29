#pragma once

#include <math/vec3.h>
#include <Mesh.h>
#include <Material.h>

struct cmp_transform
{
	vec3 position;
	float angle;
	vec3 scale;
};

ANNOTATE(cmp_transform, 
	3, 
	DEFINE_COMPONENT_MEMBER(cmp_transform, 0, vec3, position)
	DEFINE_COMPONENT_MEMBER(cmp_transform, 1, float, angle)
	DEFINE_COMPONENT_MEMBER(cmp_transform, 2, vec3, scale)
	)
DEFINE_COMPONENT_HANDLE(cmp_transform,
	COMPONENT_HANDLE_ACCESSOR(0, vec3, position)
	COMPONENT_HANDLE_ACCESSOR(1, float, angle)
	COMPONENT_HANDLE_ACCESSOR(2, vec3, scale)
)

struct cmp_render
{
	mesh* mesh;
	material material;
};

ANNOTATE(
	cmp_render,
	2,
	DEFINE_COMPONENT_MEMBER(cmp_render, 0, mesh*, mesh)
	DEFINE_COMPONENT_MEMBER(cmp_render, 1, material, material)
)

DEFINE_COMPONENT_HANDLE(cmp_render,
	COMPONENT_HANDLE_ACCESSOR(0, mesh*, mesh)
	COMPONENT_HANDLE_ACCESSOR(1, material, material)
)

struct cmp_tag
{
	std::string tag;
};

ANNOTATE(
	cmp_tag,
	1,
	DEFINE_COMPONENT_MEMBER(cmp_tag, 0, std::string, tag)
)

DEFINE_COMPONENT_HANDLE(cmp_tag,
	COMPONENT_HANDLE_ACCESSOR(0, std::string, tag)
)
