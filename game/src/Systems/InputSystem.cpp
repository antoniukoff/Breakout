#include "InputSystem.h"

#include "../Game.h"
#include "../LevelData.h"

#include <Input.h>
#include <algorithm>

InputSystem::InputSystem(Game& game)
{
	init(game);
}

void InputSystem::update()
{
	if (!game_handle)
	{
		return;
	}

	auto state = game_handle->get_state();

	switch (state)
	{
	case GameState::GAME_START:
		update_player_trajectory();
		update_camera_movement();
		break;
	case GameState::IS_ACTIVE:
		update_player_movement();
		break;
	case GameState::GAME_END:
		break;
	default:
		break;
	}
}

void InputSystem::update_player_movement()
{
	uint32_t paddle = game_handle->get_paddle_id();
	auto& registry = game_handle->get_registry();

	auto [transform] = registry.unpack<TransformComponent>(paddle);

	auto& position = transform.position();
	auto& prev_position = transform.prev_position();
	auto& scale = transform.scale();
	auto& angle = transform.angle();

	prev_position = position;

	if (Input::is_key_pressed(GLFW_KEY_A))
	{
		position += {-0.5, 0.0f, 0.0f};
	}
	if (Input::is_key_pressed(GLFW_KEY_D))
	{
		position += {0.5, 0.0f, 0.0f};
	}
	if (Input::is_key_pressed(GLFW_KEY_E))
	{
		angle -= 1.0f;
	}
	if (Input::is_key_pressed(GLFW_KEY_Q))
	{
		angle += 1.0f;
	}

	angle = std::clamp(angle, -45.0f, 45.0f);
	position.x = std::clamp(position.x, -arena_scale.x + scale.x, arena_scale.x - scale.x);

	vec3 delta_position = position - prev_position;
}

void InputSystem::update_camera_movement()
{
	auto& camera = game_handle->get_active_camera();
	auto& scene_data = game_handle->get_scene_data();

	vec3 current_target = camera.get_target_pos();
	vec3 target_target = scene_data.target_pos;

	if (Input::is_key_pressed(GLFW_KEY_A))
	{
		target_target.x += -20.0f;
	}
	if (Input::is_key_pressed(GLFW_KEY_D))
	{
		target_target.x += 20.0f;
	}

	vec3 lerped_target = vec3::lerp(current_target, target_target, 0.01f);
	
	camera.set_target(lerped_target);
}

void InputSystem::update_player_trajectory()
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
