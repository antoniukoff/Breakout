#pragma once
#include "System.h"

#include <math/vec3.h>
#include <queue>


class Game;
class Event;

class RespawnSystem : public System
{
public:
	RespawnSystem(Game& game);

	void update() override;
	
private:
	void on_brick_destroyed(const Event& event);
	void on_difficulty_increased(const Event& event);

private:
	float m_respawn_timer = 1000.0f;
	float m_elapsed = 0.0f;
	std::queue<vec3> m_available_positions;
};

