#pragma once
#include <ecs/utility.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <Mesh.h>
#include "Material.h"
#include "PowerUps.h"

struct TransformComponent
{
	TransformComponent(vec3 position)
		: position(position)
		, prev_position(position)
	{}

	TransformComponent(vec3 position, vec3 scale)
		: position(position)
		, prev_position(position)
		, scale(scale)
	{}

	vec3 position;
	vec3 prev_position;
	vec3 scale = { 1.0f, 1.0f, 1.0f };
	float angle = 0.0f;
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
	BoxColliderComponent(vec2 extents, bool is_destroyable = false)
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
	CircleColliderComponent(float radius, bool is_distructable = false)
		: radius(radius)
		, is_distructable(is_distructable)
	{}

	float radius;
	uint32_t num_hits = 0;
	bool is_distructable = false;
};

ANNOTATE(
	CircleColliderComponent,
	3,
	DEFINE_COMPONENT_MEMBER(CircleColliderComponent, 0, float, radius)
	DEFINE_COMPONENT_MEMBER(CircleColliderComponent, 1, uint32_t, num_hits)
	DEFINE_COMPONENT_MEMBER(CircleColliderComponent, 2, bool, is_distructable)
)

DEFINE_COMPONENT_HANDLE(CircleColliderComponent,
	COMPONENT_HANDLE_ACCESSOR(0, float, radius)
	COMPONENT_HANDLE_ACCESSOR(1, uint32_t, num_hits)
	COMPONENT_HANDLE_ACCESSOR(2, bool, is_distructable)
)

struct RigidBodyComponent
{
	vec3 velocity;
	float angular_velocity;
};

ANNOTATE(
	RigidBodyComponent,
	2,
	DEFINE_COMPONENT_MEMBER(RigidBodyComponent, 0, vec3, velocity)
	DEFINE_COMPONENT_MEMBER(RigidBodyComponent, 1, float, angular_velocity)
)

DEFINE_COMPONENT_HANDLE(RigidBodyComponent,
	COMPONENT_HANDLE_ACCESSOR(0, vec3, velocity)
	COMPONENT_HANDLE_ACCESSOR(1, float, angular_velocity)
)
struct LaserComponent
{
	LaserComponent(uint32_t num_balls, float duration)
		: num_balls(num_balls)
		, duration(duration)
		, cooldown((float)num_balls / duration)
	{}
	uint32_t num_balls;
	float duration;
	float cooldown;
};

ANNOTATE(
	LaserComponent,
	3,
	DEFINE_COMPONENT_MEMBER(LaserComponent, 0, uint32_t, num_balls)
	DEFINE_COMPONENT_MEMBER(LaserComponent, 1, float, duration)
	DEFINE_COMPONENT_MEMBER(LaserComponent, 2, float, cooldown)
)

DEFINE_COMPONENT_HANDLE(LaserComponent,
	COMPONENT_HANDLE_ACCESSOR(0, uint32_t, num_balls)
	COMPONENT_HANDLE_ACCESSOR(1, float, duration)
	COMPONENT_HANDLE_ACCESSOR(2, float, cooldown)
)

struct InputComponent
{
	bool is_active = false; 
};

ANNOTATE(
	InputComponent,
	1,
	DEFINE_COMPONENT_MEMBER(InputComponent, 0, bool, is_active)
)

DEFINE_COMPONENT_HANDLE(InputComponent,
	COMPONENT_HANDLE_ACCESSOR(0, bool, is_active)
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
	float duration = 0.8f;
	float time_elapsed = 0.0f;
	float intensity = 1.0f;
};

ANNOTATE(
	CameraShakeComponent,
	3,
	DEFINE_COMPONENT_MEMBER(CameraShakeComponent, 0, float, duration)
	DEFINE_COMPONENT_MEMBER(CameraShakeComponent, 1, float, time_elapsed)
	DEFINE_COMPONENT_MEMBER(CameraShakeComponent, 2, float, intensity)
)

DEFINE_COMPONENT_HANDLE(CameraShakeComponent,
	COMPONENT_HANDLE_ACCESSOR(0, float, duration)
	COMPONENT_HANDLE_ACCESSOR(1, float, time_elapsed)
	COMPONENT_HANDLE_ACCESSOR(2, float, intensity)
)

struct LifeComponent
{
	LifeComponent(uint32_t lives)
		: max_health(lives)
		, current_health(lives)
	{}
	int max_health;
	int current_health;
};

ANNOTATE(
	LifeComponent,
	2,
	DEFINE_COMPONENT_MEMBER(LifeComponent, 0, int, max_health)
	DEFINE_COMPONENT_MEMBER(LifeComponent, 1, int, current_health)
)

DEFINE_COMPONENT_HANDLE(LifeComponent,
	COMPONENT_HANDLE_ACCESSOR(0, int, max_health)
	COMPONENT_HANDLE_ACCESSOR(1, int, current_health)
)