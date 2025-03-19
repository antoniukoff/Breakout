#include "MovementSystem.h"

#include "../Game.h"

MovementSystem::MovementSystem(Game& game)
{
	init(game);
	auto& dispatcher = game.get_dispatcher();
	dispatcher.subscribe<DifficultyIncreasedEvent>(std::bind(&MovementSystem::on_diffuculty_increased_event, this, std::placeholders::_1));
}

void MovementSystem::update()
{
	auto state = game_handle->get_state();
	if (state != GameState::IS_ACTIVE)
	{
		return;
	}

	auto& registry = game_handle->get_registry();

	registry.for_each<TransformComponent, RigidBodyComponent>([this](
		entity_id e_id,
		component_handle<TransformComponent> transform_component,
		component_handle<RigidBodyComponent> movement_component)
		{
			auto& velocity = movement_component.velocity();
			auto& position = transform_component.position();
			auto& prev_position = transform_component.prev_position();

			prev_position = position;
			position += velocity;
		});
}

void MovementSystem::on_diffuculty_increased_event(const Event& event)
{
	auto& registry = game_handle->get_registry();
	registry.for_each<RigidBodyComponent>([](entity_id e, component_handle<RigidBodyComponent> rigid_body)
		{
			vec3& velocity = rigid_body.velocity();
			velocity *= 1.2f;
		});
}
