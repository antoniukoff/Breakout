#include "ParticleSystem.h"

#include "../Game.h"
#include "../GameEvents.h"
#include "ParticleBatch.h"
#include "Input.h"

#include <math/Random.h>

ParticleSystem::ParticleSystem(Game& game)
{
	init(game);

	line_handle = &game.get_line_batch();
	trail_handle = &game.get_trail_batch();
	patricle_handle = &game.get_particle_batch();
	auto& dispatcher = game.get_dispatcher();
	dispatcher.subscribe<CollisionEvent>(std::bind(&ParticleSystem::on_collision, this, std::placeholders::_1));
	dispatcher.subscribe<BrickDestroyedEvent>(std::bind(&ParticleSystem::on_brick_destroyed, this, std::placeholders::_1));
	dispatcher.subscribe<BrickRespawnEvent>(std::bind(&ParticleSystem::on_brick_respawn, this, std::placeholders::_1));
	dispatcher.subscribe<GameWonEvent>(std::bind(&ParticleSystem::on_game_won, this, std::placeholders::_1));
}

void ParticleSystem::update(float dt)
{
	GameState game_state = game_handle->get_state();
	switch (game_state)
	{
	case GameState::GAME_START:
		draw_shooting_line(dt);
		break;
	case GameState::IS_ACTIVE:
		draw_trail();
		break;
	case GameState::GAME_END:
		break;
	default:
		break;
	}
	process_emitters(dt);

	line_handle->update(dt);
	trail_handle->update(dt);
	patricle_handle->update(dt);
}

void ParticleSystem::draw_shooting_line(float dt)
{
	auto& registry = game_handle->get_registry();
	registry.for_each<TransformComponent, RigidBodyComponent>([&](entity_id e, component_handle<TransformComponent> transform, component_handle<RigidBodyComponent> rigid_body)
		{
			vec3 ball_pos = transform.position();
			vec3 ball_vel = rigid_body.velocity();

			Color particle_color;
			particle_color.r = (unsigned char)63;
			particle_color.g = (unsigned char)75;
			particle_color.b = (unsigned char)59;
			particle_color.a = (unsigned char)159;

			vec3 direction = rigid_body.velocity();
			float trail_length = 20.0f;

			const float particle_num = 35.0f;
			float particle_offset = trail_length / particle_num;

			for (uint32_t i = 0; i < particle_num; i++)
			{
				vec3 particle_pos = ball_pos + vec3::normalize(direction) * particle_offset * i;

				line_handle->add_particle(particle_pos, { 0.0f, 0.0f, 0.0f }, particle_color, 0.5f);
			}
		});
}
void ParticleSystem::draw_trail()
{
	auto& registry = game_handle->get_registry();
	registry.for_each<TransformComponent, RigidBodyComponent, CircleColliderComponent>([&](entity_id e,
		component_handle<TransformComponent> transform,
		component_handle<RigidBodyComponent> rigid_body,
		component_handle<CircleColliderComponent> _)
		{
			vec3 ball_pos = transform.position();
			vec3 ball_vel = rigid_body.velocity();

			Color particle_color;
			particle_color.r = (unsigned char)154;
			particle_color.g = (unsigned char)136;
			particle_color.b = (unsigned char)115;
			particle_color.a = (unsigned char)255;


			vec3 particle_pos = ball_pos;

			trail_handle->add_particle(particle_pos, { 0.0f, 0.0f, 0.0f }, particle_color, 0.5f);
		});
}

void ParticleSystem::process_emitters(float dt)
{
	for (int i = 0; i < m_emitters.size(); i++)
	{
		float& duration = m_emitters[i].first;
		Particle& particle = m_emitters[i].second;

		duration -= dt;
		if (duration <= 0.0f)
		{
			m_emitters[i] = m_emitters.back();
			m_emitters.pop_back();
			i--;
			continue;
		}

		float rand_x = Random::get_random_float(-20.0f, 20.0f);
		float rand_y = Random::get_random_float(-20.0f, 20.0f);
		float rand_z = Random::get_random_float(60.0f, 75.0f);

		float rand_scale = Random::get_random_float(0.25f, 0.5f);

		vec3 particle_velocity = vec3{ rand_x, rand_y, rand_z } + particle.velocity;

		patricle_handle->add_particle(particle.position, particle_velocity, particle.color, rand_scale);
	}

}

void ParticleSystem::reset()
{
	m_emitters.clear();
}

void ParticleSystem::draw(float interval)
{
	auto& camera = game_handle->get_active_camera();
	line_handle->draw(camera, interval);
	trail_handle->draw(camera, interval);
	patricle_handle->draw(camera, interval);
}


void ParticleSystem::on_collision(const Event& event)
{
	const CollisionEvent& e = static_cast<const CollisionEvent&>(event);

	uint32_t amount = (uint32_t)Random::get_random_float(25.0f, 50.0f);

	for (uint32_t i = 0; i < amount; i++)
	{
		float rand_x = Random::get_random_float(-20.0f, 20.0f);
		float rand_y = Random::get_random_float(-20.0f, 20.0f);
		float rand_z = Random::get_random_float(40.0f, 60.0f);

		Color rand_color = Random::get_random_color();

		patricle_handle->add_particle(e.position, { rand_x, rand_y, rand_z }, rand_color, 0.25f);
	}
}

void ParticleSystem::on_brick_destroyed(const Event& event)
{
	const BrickDestroyedEvent& e = static_cast<const BrickDestroyedEvent&>(event);

	Color rand_color = Random::get_random_color();

	Particle p;
	p.color = rand_color;
	p.position = e.position;

	float duration = 0.5f;
	m_emitters.push_back({ duration, p });
}

void ParticleSystem::on_brick_respawn(const Event& event)
{
	const BrickRespawnEvent& e = static_cast<const BrickRespawnEvent&>(event);

	Color rand_color = Random::get_random_color();

	Particle p;
	p.color = rand_color;
	p.position = e.position;

	float duration = 0.5f;
	m_emitters.push_back({ duration, p });
}

void ParticleSystem::on_game_won(const Event& event)
{
	auto& registry = game_handle->get_registry();
	registry.for_each<TransformComponent>([&](entity_id e, component_handle<TransformComponent> transform)
		{
			vec3 position = transform.position();
			Color rand_color = Random::get_random_color();

			Particle p;
			p.color = rand_color;
			p.position = position;
			p.velocity = vec3{ 0.0f, 0.0f, 20.0f };

			float duration = 10.0f;
			m_emitters.push_back({ duration, p });
		});
}
