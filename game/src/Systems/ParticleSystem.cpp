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
	dispatcher.subscribe<RespawnEvent>(std::bind(&ParticleSystem::on_respawn_event, this, std::placeholders::_1));
}

void ParticleSystem::update()
{
	if (!game_handle)
	{
		return;
	}
	
	GameState game_state = game_handle->get_state();
	switch (game_state)
	{
	case GameState::GAME_START:
		draw_shooting_line();
		break;
	case GameState::IS_ACTIVE:
		draw_trail();
		process_emitters();
		break;
	case GameState::GAME_END:
		break;
	default:
		break;
	}
	line_handle->update();
	trail_handle->update();
	patricle_handle->update();
}

void ParticleSystem::draw_shooting_line()
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

			const uint32_t trail_number = 50;
			for (uint32_t i = 0; i < trail_number; i++)
			{
				vec3 particle_pos = ball_pos + direction * i;

				line_handle->add_particle(particle_pos, { 0.0f, 0.0f, 0.0f }, particle_color, 0.5f);
			}
		});
}
void ParticleSystem::draw_trail()
{
	auto& registry = game_handle->get_registry();
	registry.for_each<TransformComponent, RigidBodyComponent>([&](entity_id e, component_handle<TransformComponent> transform, component_handle<RigidBodyComponent> rigid_body)
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

void ParticleSystem::process_emitters()
{
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

		patricle_handle->add_particle(particle.position, { rand_x, rand_y, rand_z }, particle.color, rand_scale);
	}

}

void ParticleSystem::reset()
{
	m_emitters.clear();
}

void ParticleSystem::draw(float interval)
{
	if (!game_handle)
	{
		return;
	}
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
		float rand_x = Random::get_random_float(-0.2f, 0.2f);
		float rand_y = Random::get_random_float(-0.2f, 0.2f);
		float rand_z = Random::get_random_float(0.2f, 0.5f);

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

	float duration = 100.0f;
	m_emitters.push_back({ duration, p });
}

void ParticleSystem::on_respawn_event(const Event& event)
{
	const RespawnEvent& e = static_cast<const RespawnEvent&>(event);

	Color rand_color = Random::get_random_color();

	Particle p;
	p.color = rand_color;
	p.position = e.position;

	float duration = 100.0f;
	m_emitters.push_back({ duration, p });
}
