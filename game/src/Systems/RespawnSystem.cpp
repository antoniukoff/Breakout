#include "RespawnSystem.h"
#include "../GameEvents.h"
#include "../Game.h"

RespawnSystem::RespawnSystem(Game& game)
{
	init(game);

	auto& dispatcher = game.get_dispatcher();
	dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&RespawnSystem::on_brick_destroyed, this, std::placeholders::_1));
	dispatcher.subscribe<DifficultyIncreasedEvent>(std::bind(&RespawnSystem::on_difficulty_increased, this, std::placeholders::_1));
	dispatcher.subscribe<LastDifficulty>(std::bind(&RespawnSystem::on_last_difficulty, this, std::placeholders::_1));
}

void RespawnSystem::update(float dt)
{
	if (m_available_positions.size() == 0)
	{
		return;
	}
	m_elapsed += dt;
	if (m_elapsed >= m_respawn_timer)
	{
		vec3 position = m_available_positions.front();

		auto& dispatcher = game_handle->get_dispatcher();

		BrickRespawnEvent event;
		event.position = position;
		dispatcher.dispatch(event);

		m_available_positions.pop();

		m_elapsed = 0.0f;
	}
}

void RespawnSystem::reset()
{
	m_respawn_timer = m_max_respawn_time;
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
	m_respawn_timer -= 2.0f;
}

void RespawnSystem::on_last_difficulty(const Event& event)
{
}

