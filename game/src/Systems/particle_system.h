#pragma once
#include "system.h"

#include <math/vec3.h>
#include <utility>
#include <vector>
#include <particle_batch.h>

class Game;
class EventBase;

class ParticleSystem : public System
{
	using emitters = std::vector<std::pair<float, Particle>>;
public:
	ParticleSystem(Game& game);
	void update(float dt) override;
	void draw_shooting_line(float dt);
	void draw_trail();
	void process_emitters(float dt);
	void reset();
	void draw(float interval);
private:
	void on_collision(const EventBase& event);
	void on_brick_destroyed(const EventBase& event);
	void on_brick_respawn(const EventBase& event);
	void on_game_won(const EventBase& event);

private:
	emitters m_emitters;
	ParticleBatch* line_handle;
	ParticleBatch* trail_handle;
	ParticleBatch* patricle_handle;

};

