#include "HealthSystem.h"

#include "../Game.h"
#include "../GameEvents.h"


HealthSystem::HealthSystem(Game& game)
{
	init(game);

	auto& dispacther = game.get_dispatcher();
	dispacther.subscribe<CollisionEvent>(std::bind(&HealthSystem::on_collision_event, this, std::placeholders::_1));
}

void HealthSystem::on_collision_event(const Event& event)
{
	const CollisionEvent& ce = static_cast<const CollisionEvent&>(event);
	auto& registry = game_handle->get_registry();
	if (registry.has<LifeComponent>(ce.entity_id))
	{
		auto [health_component] = registry.unpack<LifeComponent>(ce.entity_id);
		auto& curr_health = health_component.current_health();
		curr_health--;

		if (curr_health <= 0)
		{
			auto [transform] = registry.unpack<TransformComponent>(ce.entity_id);
			auto& dispatcher = game_handle->get_dispatcher();

			BrickDestroyedEvent be;
			be.position = transform.position();
			dispatcher.dispatch(be);

			registry.destroy(ce.entity_id);
		}
	}
}

void HealthSystem::update()
{
}
