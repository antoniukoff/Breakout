#pragma once

#include <math/vec3.h>
#include <Mesh.h>
#include <Material.h>

struct Transform
{
	vec3 position;
	float angle;
	vec3 scale;
};

ANNOTATE(Transform, 
	3, 
	DEFINE_COMPONENT_MEMBER(Transform, 0, vec3, position)
	DEFINE_COMPONENT_MEMBER(Transform, 1, float, angle)
	DEFINE_COMPONENT_MEMBER(Transform, 2, vec3, scale)
	)
DEFINE_COMPONENT_HANDLE(Transform,
	COMPONENT_HANDLE_ACCESSOR(0, vec3, position)
	COMPONENT_HANDLE_ACCESSOR(1, float, angle)
	COMPONENT_HANDLE_ACCESSOR(2, vec3, scale)
)

struct RenderComponent
{
	Mesh* mesh;
	Material material;
};

ANNOTATE(
	RenderComponent,
	2,
	DEFINE_COMPONENT_MEMBER(RenderComponent, 0, Mesh*, mesh)
	DEFINE_COMPONENT_MEMBER(RenderComponent, 1, Material, material)
)

DEFINE_COMPONENT_HANDLE(RenderComponent,
	COMPONENT_HANDLE_ACCESSOR(0, Mesh*, mesh)
	COMPONENT_HANDLE_ACCESSOR(1, Material, material)
)

struct TagComponent
{
	std::string tag;
};

ANNOTATE(
	TagComponent,
	1,
	DEFINE_COMPONENT_MEMBER(TagComponent, 0, std::string, tag)
)

DEFINE_COMPONENT_HANDLE(TagComponent,
	COMPONENT_HANDLE_ACCESSOR(0, std::string, tag)
)

struct Sample
{
	std::vector<Material> mat;
};

ANNOTATE(
	Sample,
	1,
	DEFINE_COMPONENT_MEMBER(Sample, 0, std::vector<Material>, mat)
)

DEFINE_COMPONENT_HANDLE(Sample,
	COMPONENT_HANDLE_ACCESSOR(0, std::vector<Material>, mat)
)