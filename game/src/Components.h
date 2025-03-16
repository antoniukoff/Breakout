#pragma once
#include <ecs/utility.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <Mesh.h>
#include "Material.h"

struct TransformComponent
{
	vec3 position;
	vec3 prev_position;
	vec3 scale = { 1.0f, 1.0f, 1.0f };
	float angle = 0.0f;

	bool is_dirty = true;
};

ANNOTATE(
	TransformComponent,
	4, 
	DEFINE_COMPONENT_MEMBER(TransformComponent, 0, vec3, position)
	DEFINE_COMPONENT_MEMBER(TransformComponent, 1, vec3, prev_position)
	DEFINE_COMPONENT_MEMBER(TransformComponent, 2, vec3, scale)
	DEFINE_COMPONENT_MEMBER(TransformComponent, 3, float, angle)
)

DEFINE_COMPONENT_HANDLE(TransformComponent,
	COMPONENT_HANDLE_ACCESSOR(0, vec3, position)
	COMPONENT_HANDLE_ACCESSOR(1, vec3, prev_position)
	COMPONENT_HANDLE_ACCESSOR(2, vec3, scale)
	COMPONENT_HANDLE_ACCESSOR(3, float, angle)
)

struct BoxColliderComponent
{
	BoxColliderComponent(vec2 extents)
		: extents(extents)
		, half_extents(extents / 2.0f)
	{}
	vec2 extents;
	vec2 half_extents;
};

ANNOTATE(
	BoxColliderComponent,
	2,
	DEFINE_COMPONENT_MEMBER(BoxColliderComponent, 0, vec2, extents)
	DEFINE_COMPONENT_MEMBER(BoxColliderComponent, 1, vec2, half_extents)
)

DEFINE_COMPONENT_HANDLE(BoxColliderComponent,
	COMPONENT_HANDLE_ACCESSOR(0, vec2, extents)
	COMPONENT_HANDLE_ACCESSOR(1, vec2, half_extents)
)

struct CircleColliderComponent
{
	float radius;
	uint32_t num_hits = 0;
};

ANNOTATE(
	CircleColliderComponent,
	2,
	DEFINE_COMPONENT_MEMBER(CircleColliderComponent, 0, float, radius)
	DEFINE_COMPONENT_MEMBER(CircleColliderComponent, 1, uint32_t, num_hits)
)

DEFINE_COMPONENT_HANDLE(CircleColliderComponent,
	COMPONENT_HANDLE_ACCESSOR(0, float, radius)
	COMPONENT_HANDLE_ACCESSOR(1, uint32_t, num_hits)
)

struct RigidBodyComponent
{
	vec3 velocity;
};

ANNOTATE(
	RigidBodyComponent,
	1,
	DEFINE_COMPONENT_MEMBER(RigidBodyComponent, 0, vec3, velocity)
)

DEFINE_COMPONENT_HANDLE(RigidBodyComponent,
	COMPONENT_HANDLE_ACCESSOR(0, vec3, velocity)
)

struct InputComponent
{
	bool left = false; 
	bool right = false; 
	bool tilt_left = false; 
	bool tile_right = false;
};

ANNOTATE(
	InputComponent,
	4,
	DEFINE_COMPONENT_MEMBER(InputComponent, 0, bool, left)
	DEFINE_COMPONENT_MEMBER(InputComponent, 1, bool, right)
	DEFINE_COMPONENT_MEMBER(InputComponent, 2, bool, tilt_left)
	DEFINE_COMPONENT_MEMBER(InputComponent, 3, bool, tile_right)
)

DEFINE_COMPONENT_HANDLE(InputComponent,
	COMPONENT_HANDLE_ACCESSOR(0, bool, left)
	COMPONENT_HANDLE_ACCESSOR(1, bool, right)
	COMPONENT_HANDLE_ACCESSOR(2, bool, tilt_left)
	COMPONENT_HANDLE_ACCESSOR(3, bool, tile_right)
)

struct RenderComponent
{
	Mesh* mesh;
	Material* material;
};

ANNOTATE(
	RenderComponent,
	2,
	DEFINE_COMPONENT_MEMBER(RenderComponent, 0, Mesh*, mesh)
	DEFINE_COMPONENT_MEMBER(RenderComponent, 1, Material*, material)
)

DEFINE_COMPONENT_HANDLE(RenderComponent,
	COMPONENT_HANDLE_ACCESSOR(0, Mesh*, mesh)
	COMPONENT_HANDLE_ACCESSOR(1, Material*, material)
)

struct CameraShakeComponent
{
	bool is_active = false;
	float duration = 5.0f;
	float time_elapsed = 0.0f;
	float intensity = 1.0f;
};

ANNOTATE(
	CameraShakeComponent,
	4,
	DEFINE_COMPONENT_MEMBER(CameraShakeComponent, 0, bool, is_active)
	DEFINE_COMPONENT_MEMBER(CameraShakeComponent, 1, float, duration)
	DEFINE_COMPONENT_MEMBER(CameraShakeComponent, 2, float, time_elapsed)
	DEFINE_COMPONENT_MEMBER(CameraShakeComponent, 3, float, intensity)
)

DEFINE_COMPONENT_HANDLE(CameraShakeComponent,
	COMPONENT_HANDLE_ACCESSOR(0, bool, is_active)
	COMPONENT_HANDLE_ACCESSOR(1, float, duration)
	COMPONENT_HANDLE_ACCESSOR(2, float, time_elapsed)
	COMPONENT_HANDLE_ACCESSOR(3, float, intensity)
)