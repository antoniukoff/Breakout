#pragma once
#include "system.h"
#include "../game_events.h"

#include <math/vec3.h>
#include <queue>

class Game;
class EventBase;

class RespawnSystem : public System
{
public:
	RespawnSystem(Game& game);
	void update(float dt) override;
	void reset();
	
private:
	void on_brick_destroyed(const BrickDestroyedEvent& event);
	void on_difficulty_increased(const EventBase& event);

private:
	const float m_max_respawn_time = 20.0f;

	float m_respawn_timer = m_max_respawn_time;
	float m_elapsed = 0.0f;
	std::queue<vec3> m_available_positions;
};

