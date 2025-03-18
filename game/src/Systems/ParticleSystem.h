#pragma once
#include "System.h"

#include <math/vec3.h>
#include <utility>
#include <vector>
#include <ParticleBatch.h>

class Game;
class Event;

class ParticleSystem : public System
{
	using emitters = std::vector<std::pair<float, Particle>>;
public:
	ParticleSystem(Game& game);
	void update() override;
	void draw(Camera& camera, float interval);
private:
	void on_collision(const Event& event);
	void on_brick_destroyed(const Event& event);

private:
	emitters m_emitters;
	ParticleBatch* batch_handle;
	Game* game_handle;
};

