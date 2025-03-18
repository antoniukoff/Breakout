#include "RespawnSystem.h"
#include "../GameEvents.h"
#include "../ScenaLoader.h"
#include "../Game.h"

RespawnSystem::RespawnSystem(Game& game)
{
	init(game);

	auto& dispatcher = game.get_dispatcher();
	dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&RespawnSystem::on_brick_destroyed, this, std::placeholders::_1));
}

void RespawnSystem::update()
{
	if (!game_handle)
	{
		return;
	}

	m_elapsed++;
	if (m_elapsed >= m_respawn_timer)
	{
		if (m_available_positions.size() > 0)
		{
			vec3 position = m_available_positions.front();
			ScenaLoader::create_brick(*game_handle, position);
			m_available_positions.pop();
		}
		m_elapsed = 0.0f;
	}
}

void RespawnSystem::on_brick_destroyed(const Event& event)
{
	const BrickDestroyedEvent& e = static_cast<const BrickDestroyedEvent&>(event);
	m_available_positions.push(e.position);
}

void RespawnSystem::on_difficulty_increased(const Event& event)
{
	const BrickDestroyedEvent& e = static_cast<const BrickDestroyedEvent&>(e);
	m_available_positions.push(e.position);
}


