#include "PhysicsSystem.h"

#include "../Game.h"
#include "../GameEvents.h"
#include "../LevelData.h"
#include <algorithm>

#include <math/Random.h>

PhysicsSystem::PhysicsSystem(Game& game)
{
	init(game);
}

void PhysicsSystem::update(float dt)
{
	auto state = game_handle->get_state();
	if (state != GameState::IS_ACTIVE)
	{
		return;
	}

	check_player_level_bounds();
	update_ball_box_collision();
}

void PhysicsSystem::check_player_level_bounds()
{
	auto& registry = game_handle->get_registry();
	auto& dispatcher = game_handle->get_dispatcher();

	registry.for_each<TransformComponent, RigidBodyComponent, BoxColliderComponent>([&](
		entity_id circle,
		component_handle<TransformComponent>   paddle_transform,
		component_handle<RigidBodyComponent>   paddle_movement,
		component_handle<BoxColliderComponent> paddle_collider)
		{
			float& position_x		= paddle_transform.position().x;
			float  paddle_extent_x = paddle_collider.half_extents().x;
			position_x = std::clamp(position_x, -arena_scale.x + paddle_extent_x, arena_scale.x - paddle_extent_x);
		});
}

void PhysicsSystem::update_ball_box_collision()
{
	auto& registry = game_handle->get_registry();
	auto& dispatcher = game_handle->get_dispatcher();

	registry.for_each<TransformComponent, RigidBodyComponent, BounceComponent, CircleColliderComponent>([&](
		entity_id circle,
		component_handle<TransformComponent> circle_transform,
		component_handle<RigidBodyComponent> circle_movement,
		component_handle<BounceComponent> ball_bounce,
		component_handle<CircleColliderComponent> circle_collider)
		{
			/// Ball Data
			vec3& ball_pos = circle_transform.position();
			vec3& ball_prev_pos = circle_transform.prev_position();
			vec3& ball_velocity = circle_movement.velocity();
			float ball_radius = circle_collider.radius();

			registry.for_each<TransformComponent, BoxColliderComponent>([&](
				entity_id box,
				component_handle<TransformComponent> paddle_transform,
				component_handle<BoxColliderComponent> box_collider)
				{
					/// Bricks and paddle data
					vec3& box_pos = paddle_transform.position();
					float box_angle = paddle_transform.angle();
					vec2 box_extents = box_collider.half_extents();

					CollisionData collision = check_OBB_Circle_collision(ball_pos, ball_radius, box_pos, box_extents, box_angle);
					bool collided = collision.collided;
					vec2 distance = collision.collision_vector;

					if (collided)
					{
						vec3 best_normal = calculate_best_normal(distance);

						/// Rotate the normal with the paddle
						mat4::mult_vec_by_mat(mat4::rotate_z(box_angle), best_normal);

						vec3 world_collision_point = ball_pos - best_normal * (ball_radius + distance.mag());

						CollisionEvent e;
						e.entity_id = box;
						e.position = world_collision_point;
						dispatcher.dispatch(e);

						ball_prev_pos = ball_pos;
						ball_pos += best_normal * (ball_radius - distance.mag() + 0.5f);

						/// Project velocwity onto the normal --- no need for normals dot product since its a unit length
						ball_velocity = vec3::reflect(ball_velocity, best_normal);
						if (box == game_handle->get_paddle_id())
						{
							if (ball_bounce.impulse_strength() > 0.0f)
							{
								return;
							}
							ball_bounce.impulse_strength() = 50.0f;
							ball_bounce.impulse_time() = 0.5f;
							ball_bounce.base_speed() = ball_velocity.mag();
						}
					}
					else
					{
						/// Check if the ball is below paddle
						if (box == game_handle->get_paddle_id())
						{
							vec3 point_of_no_return = calculate_paddle_lowest_point(box_pos, collision.closest_point, box_extents.to_vec3(), box_angle);

							if (ball_pos.y - ball_radius < point_of_no_return.y)
							{
								dispatcher.dispatch(BallRespawnEvent{});
							}
						}
					}
				});
		});
}

CollisionData PhysicsSystem::check_OBB_Circle_collision(const vec3& ball_pos, float radius, const vec3& box_pos, const vec2& collider_half_dims, float box_angle)
{
	vec3 local_ball_position = ball_pos - box_pos;

	/// Rotate ball into boxes local space
	mat4::mult_vec_by_mat(mat4::rotate_z(-box_angle), local_ball_position);

	vec2 local_ball_2D = { local_ball_position.x, local_ball_position.y };

	/// Clamp to get the closest point on the collider
	vec2 closest_point = vec2::clamp(local_ball_2D, -collider_half_dims, collider_half_dims);

	/// Vector from point on the bounds to the balls position in paddles local space
	vec2 collision_vector = local_ball_2D - closest_point;

	float length = collision_vector.mag();

	vec3 closest_point3D = vec3{ closest_point.x, closest_point.y, 0.0f };
	return { length <= radius, collision_vector, closest_point3D };
}

vec3 PhysicsSystem::calculate_paddle_lowest_point(const vec3& paddle_pos, const vec3& collider_collision_point, const vec3& box_extents, float paddle_angle)
{
	/// Only check the left and right side of the paddle
	vec3 best_normal = collider_collision_point.x > 0.0f ? vec3{ 1.0, 0.0f,0.0f } : vec3{ -1.0f, 0.0f, 0.0f };

	/// Get the bottom left or right point on the boxes collider in local space
	vec3 local_point_of_no_return = best_normal * box_extents;
	local_point_of_no_return.y -= box_extents.y;

	/// Rotate the point with the boxes angle
	mat4::mult_vec_by_mat(mat4::rotate_z(paddle_angle), local_point_of_no_return);

	/// Flip the side if the checking side is tilted up
	if (local_point_of_no_return.y > 0.0f)
	{
		local_point_of_no_return = -local_point_of_no_return;
	}

	/// Return the point in the world space
	return paddle_pos + local_point_of_no_return;
}

vec3 PhysicsSystem::calculate_best_normal(vec2 distance_vec)
{
	//// Define normals of the cube
	constexpr vec2 box_normals[4] =
	{
		vec2{  0.0f,  1.0f }, // up
		vec2{  0.0f, -1.0f }, // down
		vec2{  1.0f,  0.0f }, // left
		vec2{ -1.0f,  0.0f }  // right
	};

	float max = 0.0f;
	int best_match = -1;

	//// Get the dot product of the four sides
	for (uint32_t i = 0; i < 4; i++)
	{

		float dot = vec2::dot(distance_vec, box_normals[i]);
		if (dot > max)
		{
			/// Get the best match
			max = dot;
			best_match = i;
		}
	}

	vec2 normal = box_normals[best_match];
	return { normal.x, normal.y, 0.0f };
}
