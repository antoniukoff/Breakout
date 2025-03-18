#include "MovementSystem.h"

#include "../Game.h"

MovementSystem::MovementSystem(Game& game)
{
	init(game);
}

void MovementSystem::update()
{
	if (!game_handle)
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
