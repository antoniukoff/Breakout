#include "CameraSystem.h"

#include "../Game.h"

#include <math/Random.h>

CameraSystem::CameraSystem(Game& game)
{
	init(game);

	auto& dispatcher_handle = game.get_dispatcher();
	dispatcher_handle.subscribe<CollisionEvent>(std::bind(&CameraSystem::on_collision, this, std::placeholders::_1));
	dispatcher_handle.subscribe<BallRespawnEvent>(std::bind(&CameraSystem::on_ball_respawn, this, std::placeholders::_1));
	dispatcher_handle.subscribe<GameWonEvent>(std::bind(&CameraSystem::on_ball_respawn, this, std::placeholders::_1));
}

void CameraSystem::update(float dt)
{
	auto game_state = game_handle->get_state();
	switch (game_state)
	{
	case GameState::IS_ACTIVE:
		update_camera_shake(dt);
		break;
	default:
		break;
	}
	smooth_camera_position(dt);
}

void CameraSystem::update_camera_shake(float dt)
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

	time_elapsed += dt;

	if (time_elapsed >= shake_duration)
	{
		entity_processing = -1;
		time_elapsed = 0.0f;
		return;
	}

	/// fade out the camera shake over time
	float strength = intensity * (1.0f - time_elapsed / shake_duration);

	float yaw_offset = Random::get_random_float(-0.5f, 0.5f) * strength;
	float pitch_offset = Random::get_random_float(-0.5f, 0.5f) * strength;

	camera.add_yaw(yaw_offset);
	camera.add_pitch(pitch_offset);
}

void CameraSystem::smooth_camera_position(float dt)
{
	auto& registry = game_handle->get_registry();
	auto& camera = game_handle->get_active_camera();
	auto& scene_data = game_handle->get_scene_data();

	auto [paddle_transform] = registry.unpack<TransformComponent>(game_handle->get_paddle_id());

	float paddle_x = paddle_transform.position().x;

	vec3 target_position = scene_data.camera_pos;
	target_position.x = paddle_x;
	vec3 target_target = scene_data.target_pos;
	target_target.x = paddle_x;

	vec3 camera_pos = camera.get_position();
	vec3 camera_target = camera.get_target_pos();

	vec3 lerped_camera_pos = vec3::lerp(camera_pos, target_position, dt);
	vec3 lerped_target_pos = vec3::lerp(camera_target, target_target, dt);

	camera.set_position(lerped_camera_pos);
	camera.set_target(lerped_target_pos);
}

void CameraSystem::reset()
{
	auto& camera = game_handle->get_active_camera();

	camera.add_yaw(0.0f);
	camera.add_pitch(0.0f);

	if (entity_processing == -1)
	{
		return;
	}

	auto& registry = game_handle->get_registry();
	auto [shake_component] = registry.unpack<CameraShakeComponent>(entity_processing);
	shake_component.time_elapsed() = 0;

	entity_processing = -1;
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

void CameraSystem::on_ball_respawn(const Event& event)
{
	reset();
}

