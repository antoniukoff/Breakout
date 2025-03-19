#include "CameraSystem.h"

#include "../Game.h"

#include <math/Random.h>

CameraSystem::CameraSystem(Game& game)
{
	init(game);

	auto& dispatcher_handle = game.get_dispatcher();
	dispatcher_handle.subscribe<CollisionEvent>(std::bind(&CameraSystem::on_collision, this, std::placeholders::_1));
}

void CameraSystem::update()
{
	auto game_state = game_handle->get_state();
	switch (game_state)
	{
	case GameState::GAME_START:
		smooth_camera_position();
		break;
	case GameState::IS_ACTIVE:
		update_camera_shake();
		smooth_camera_position();
		break;
	case GameState::GAME_END:
		break;
	default:
		break;
	}
	
}

void CameraSystem::update_camera_shake()
{

	if (entity_processing == -1)
	{
		return;
	}

	auto& registry = game_handle->get_registry();
	auto& camera = game_handle->get_active_camera();

	auto [shake_component] = registry.unpack<CameraShakeComponent>(entity_processing);

	float intensity = shake_component.intensity();
	float& time_elapsed = shake_component.time_elapsed();
	float shake_duration = shake_component.duration();

	time_elapsed += 0.05f;

	if (time_elapsed >= shake_duration)
	{
		entity_processing = -1;
		time_elapsed = 0.0f;
		return;
	}

	/// fade out the camera shake
	float strength = intensity * (1.0f - time_elapsed / shake_duration);

	float yaw_offset = Random::get_random_float(-0.5f, 0.5f) * strength;
	float pitch_offset = Random::get_random_float(-0.5f, 0.5f) * strength;

	camera.add_yaw(yaw_offset);
	camera.add_pitch(pitch_offset);
}

void CameraSystem::smooth_camera_position()
{
	auto& registry = game_handle->get_registry();
	auto& camera = game_handle->get_active_camera();
	auto& scene_data = game_handle->get_scene_data();

	auto [transform] = registry.unpack<TransformComponent>(game_handle->get_paddle_id());
	vec3 position = transform.position();

	vec3 target_position = scene_data.camera_pos;
	vec3 target_target = scene_data.target_pos;
	target_position.x = position.x;
	target_target.x = position.x;

	vec3 camera_pos = camera.get_position();
	vec3 target_pos = camera.get_target_pos();

	vec3 lerped_camera_pos = vec3::lerp(camera_pos, target_position, 0.01f);
	vec3 lerped_target_pos = vec3::lerp(target_pos, target_target, 0.01f);

	camera.set_position(lerped_camera_pos);
	camera.set_target(lerped_target_pos);
}



void CameraSystem::on_collision(const Event& event)
{
	if (entity_processing != -1)
	{
		return;
	}
	const CollisionEvent& e = static_cast<const CollisionEvent&>(event);
	entity_processing = e.entity_id;
}


