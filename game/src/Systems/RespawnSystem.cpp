#include "RespawnSystem.h"
#include "../GameEvents.h"
#include "../ScenaLoader.h"
#include "../Game.h"

RespawnSystem::RespawnSystem(Game& game)
{
	init(game);

	auto& dispatcher = game.get_dispatcher();
	dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&RespawnSystem::on_brick_destroyed, this, std::placeholders::_1));
	dispatcher.subscribe<DifficultyIncreasedEvent>(std::bind(&RespawnSystem::on_difficulty_increased, this, std::placeholders::_1));
	dispatcher.subscribe<LastDifficulty>(std::bind(&RespawnSystem::on_last_difficulty, this, std::placeholders::_1));
}

void RespawnSystem::init(Game& game)
{
	game_handle = &game;
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

			auto& dispatcher = game_handle->get_dispatcher();
			RespawnEvent event;
			event.position = position;
			dispatcher.dispatch(event);
		}
		m_elapsed = 0.0f;
	}
}

void RespawnSystem::reset()
{
	if (game_handle)
	{
		game_handle = nullptr;
	}
	m_respawn_timer = 2500.0f;
	m_elapsed = 0.0f;

	std::queue<vec3> new_queue;
	std::swap(m_available_positions, new_queue);
}

void RespawnSystem::on_brick_destroyed(const Event& event)
{
	const BrickDestroyedEvent& e = static_cast<const BrickDestroyedEvent&>(event);
	m_available_positions.push(e.position);
}

void RespawnSystem::on_difficulty_increased(const Event& event)
{
	m_respawn_timer / 2.0f;
}

void RespawnSystem::on_last_difficulty(const Event& event)
{
	m_respawn_timer = 2000.0f;
}

