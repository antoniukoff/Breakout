#include "InputSystem.h"

#include "../Game.h"
#include "../LevelData.h"

#include <Input.h>
#include <algorithm>

InputSystem::InputSystem(Game& game)
{
	init(game);
}

void InputSystem::update(float dt)
{
	auto state = game_handle->get_state();

	switch (state)
	{
	case GameState::GAME_START:
		update_initial_movement_dir(dt);
		update_camera_movement(dt);
		break;
	case GameState::IS_ACTIVE:
		update_player_movement(dt);
		break;
	case GameState::GAME_END:
		update_camera_movement(dt);
		break;
	default:
		break;
	}
}

void InputSystem::update_player_movement(float dt)
{
	const float movement_speed = 100.0f; 
	const float rotation_speed = 90.0f;  

	uint32_t paddle = game_handle->get_paddle_id();
	auto& registry  = game_handle->get_registry();

	auto [rigid_body] = registry.unpack<RigidBodyComponent>(paddle);

	auto& velocity = rigid_body.velocity();
	auto& angular  = rigid_body.angular_velocity();

	velocity = vec3();
	angular = 0.0f;

	if (Input::is_key_pressed(GLFW_KEY_A))
	{
		velocity.x -= movement_speed;
	}
	if (Input::is_key_pressed(GLFW_KEY_D))
	{
		velocity.x += movement_speed;
	}
	if (Input::is_key_pressed(GLFW_KEY_E))
	{
		angular -= rotation_speed;
	}
	if (Input::is_key_pressed(GLFW_KEY_Q))
	{
		angular += rotation_speed;
	}
}

void InputSystem::update_camera_movement(float dt)
{
	auto& camera = game_handle->get_active_camera();

	vec3 current_target = camera.get_target_pos();

	vec3 new_target = current_target;
	if (Input::is_key_pressed(GLFW_KEY_A))
	{
		new_target.x -= 20;
	}
	if (Input::is_key_pressed(GLFW_KEY_D))
	{
		new_target.x += 20;
	}
	vec3 lerped_target = vec3::lerp(current_target, new_target, dt);
	camera.set_target(lerped_target);
}

void InputSystem::update_initial_movement_dir(float dt)
{
	float angle = 0.0f;

	if (Input::is_key_pressed(GLFW_KEY_Q))
	{
		angle = 1.0f;
	}
	if (Input::is_key_pressed(GLFW_KEY_E))
	{
		angle = -1.0f;
	}

	auto& registry = game_handle->get_registry();
	registry.for_each<RigidBodyComponent>([&](entity_id e, component_handle<RigidBodyComponent> rigid_body)
		{
			vec3& velocity = rigid_body.velocity();
			mat4 rotation = mat4::rotate_z(angle);

			mat4::mult_vec_by_mat(rotation, velocity);
		});
}
