#include "RespawnSystem.h"
#include "../GameEvents.h"
#include "../Game.h"

RespawnSystem::RespawnSystem(Game& game)
{
	init(game);

	auto& dispatcher = game.get_dispatcher();
	dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&RespawnSystem::on_brick_destroyed, this, std::placeholders::_1));
	dispatcher.subscribe<DifficultyIncreasedEvent>(std::bind(&RespawnSystem::on_difficulty_increased, this, std::placeholders::_1));
}

void RespawnSystem::update(float dt)
{
	auto game_state = game_handle->get_state();
	if (m_available_positions.size() == 0 || game_state == GameState::GAME_END)
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
	float min_respawn_amount = 5.0f;

	float current_level = game_handle->get_current_level();
	float total_difficulties = game_handle->get_level_diffuculties();
	float total_levels = 2.0f;

	float level_ratio = current_level / total_levels;

	float level_respawn_ratio = (level_ratio + 1.0f) * 0.5f;

	float min_respawn_time_for_the_level = m_max_respawn_time - (level_respawn_ratio * (m_max_respawn_time - min_respawn_amount));

	float respawn_offset = (m_max_respawn_time - min_respawn_time_for_the_level) / (total_difficulties - 1);

	m_respawn_timer -= respawn_offset;
}


