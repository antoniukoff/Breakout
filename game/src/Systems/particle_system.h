#pragma once
#include "system.h"

#include <math/vec3.h>
#include <utility>
#include <vector>
#include <particle_batch.h>

class Game;
class event_base;

class ParticleSystem : public System
{
	using emitters = std::vector<std::pair<float, particle>>;
public:
	ParticleSystem(Game& game);
	void update(float dt) override;
	void draw_shooting_line(float dt);
	void draw_trail();
	void process_emitters(float dt);
	void reset();
	void draw(float interval);
private:
	void on_collision(const event_base& event);
	void on_brick_destroyed(const event_base& event);
	void on_brick_respawn(const event_base& event);
	void on_game_won(const event_base& event);

private:
	emitters m_emitters;
	particle_group* line_handle;
	particle_group* trail_handle;
	particle_group* patricle_handle;

};

