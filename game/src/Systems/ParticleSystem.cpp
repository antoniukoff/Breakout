#include "ParticleSystem.h"

#include "../Game.h"
#include "../GameEvents.h"
#include "ParticleBatch.h"

#include <math/Random.h>


ParticleSystem::ParticleSystem(Game& game)
{
	init(game);

	batch_handle = &game.get_particle_batch();
	auto& dispatcher = game.get_dispatcher();
	dispatcher.subscribe<CollisionEvent>(std::bind(&ParticleSystem::on_collision, this, std::placeholders::_1));
	dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&ParticleSystem::on_brick_destroyed, this, std::placeholders::_1));
}

void ParticleSystem::update()
{
	if (!game_handle)
	{
		return;
	}

	for (int i = 0; i < m_emitters.size(); i++)
	{
		float& duration = m_emitters[i].first;
		Particle& particle = m_emitters[i].second;

		duration--;
		if (duration <= 0.0f)
		{
			m_emitters[i] = m_emitters.back();
			m_emitters.pop_back();
			i--;
		}

		float rand_x = Random::get_random_float(-0.2f, 0.2f);
		float rand_y = Random::get_random_float(-0.2f, 0.2f);
		float rand_z = Random::get_random_float(0.2f, 0.5f);
		float rand_scale = Random::get_random_float(0.25f, 0.5f);

		batch_handle->add_particle(particle.position, { rand_x, rand_y, rand_z }, particle.color, rand_scale);
	}

	batch_handle->update();
}

void ParticleSystem::draw(Camera& camera, float interval)
{
	batch_handle->draw(camera, interval);
}


void ParticleSystem::on_collision(const Event& event)
{
	const CollisionEvent& e = static_cast<const CollisionEvent&>(event);

	uint32_t amount = (uint32_t)Random::get_random_float(25.0f, 50.0f);

	for (uint32_t i = 0; i < amount; i++)
	{
		float rand_x = Random::get_random_float(-0.2f, 0.2f);
		float rand_y = Random::get_random_float(-0.2f, 0.2f);
		float rand_z = Random::get_random_float(0.2f, 0.5f);

		Color rand_color = Random::get_random_color();

		batch_handle->add_particle(e.position, { rand_x, rand_y, rand_z }, rand_color, 0.25f);
	}
}

void ParticleSystem::on_brick_destroyed(const Event& event)
{
	const BrickDestroyedEvent& e = static_cast<const BrickDestroyedEvent&>(event);

	Color rand_color = Random::get_random_color();

	Particle p;
	p.color = rand_color;
	p.position = e.position;

	float duration = 100.0f;
	m_emitters.push_back({ duration, p });
}
