#include "MovementSystem.h"

#include "../Game.h"

MovementSystem::MovementSystem(Game& game)
{
	init(game);
	auto& dispatcher = game.get_dispatcher();
	dispatcher.subscribe<DifficultyIncreasedEvent>(std::bind(&MovementSystem::on_diffuculty_increased_event, this, std::placeholders::_1));
}

void MovementSystem::update(float dt)
{
	auto state = game_handle->get_state();
	if (state != GameState::IS_ACTIVE)
	{
		return;
	}

	auto& registry = game_handle->get_registry();

	registry.for_each<RigidBodyComponent, BounceComponent>([&](
		entity_id e_id,
		component_handle<RigidBodyComponent> movement_component,
		component_handle<BounceComponent> bounce_component)
		{
			vec3& velocity = movement_component.velocity();

			float base_speed = bounce_component.base_speed();
			float total_time = bounce_component.impulse_time();
			float& elapsed_time = bounce_component.elapsed_time();
			float& impulse_strength = bounce_component.impulse_strength();

			if (impulse_strength == 0.0f)
			{
				return;
			}
			elapsed_time += dt;
			if (elapsed_time >= total_time)
			{
				velocity = vec3::normalize(velocity) * base_speed;
				elapsed_time = 0.0f;
				impulse_strength = 0.0f;
				return;
			}
			
			float impulse = (1.0f - (elapsed_time / total_time)) * impulse_strength;

			float actual_impulse = base_speed + impulse;

			velocity = vec3::normalize(velocity) * actual_impulse;
		});

	registry.for_each<TransformComponent, RigidBodyComponent>([&](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<RigidBodyComponent> movement_component)
		{
			auto& velocity = movement_component.velocity();
			auto& angular  = movement_component.angular_velocity();
			auto& position = transform_component.position();
			auto& angle = transform_component.angle();

			auto& prev_position = transform_component.prev_position();

			prev_position = position;

			position += velocity * dt;
			angle += angular * dt;
			angle = std::clamp(angle, -45.0f, 45.0f);
		});
}

void MovementSystem::on_diffuculty_increased_event(const Event& event)
{
	auto& registry = game_handle->get_registry();
	registry.for_each<RigidBodyComponent>([](entity_id e, component_handle<RigidBodyComponent> rigid_body)
		{
			vec3& velocity = rigid_body.velocity();
			velocity *= 1.1f;
		});
}
