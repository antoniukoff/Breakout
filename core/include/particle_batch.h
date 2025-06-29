#pragma once
#include "math/vec3.h"
#include <functional>
#include "color.h"
#include "shader.h"

class mesh;
class camera;

class particle 
{
public:
	vec3 position;
	vec3 prev_position;
	vec3 velocity;
	color color;
	float life = 0.0f;
	float scale = 0.0f;	
};

inline void default_particle_update(particle& particle, float dt)
{
	const float gravity = 115; 

	particle.velocity.z -= gravity * dt;
	particle.prev_position = particle.position;
	particle.position += particle.velocity * dt;

	particle.color.a = (unsigned char)(particle.life * 255.0f);
}

class particle_group
{
public:
	particle_group();
	~particle_group();

	void initizalize(uint32_t max_particles, float decay_rate, mesh* mesh, std::function<void(particle&, float)> update_func = default_particle_update);
	void update(float dt);
	void draw(camera& camera, float interval);
	void add_particle(const vec3& position,
		const vec3& velocity,
		const color& color,
		float scale);


	inline uint32_t get_capacity() const { return m_max_marticles; }

private:
	//// Particle Data
	bool	  m_initialized = false;
	uint32_t  m_size = 0;
	uint32_t  m_max_marticles = 0;
	float	  m_decay_rate = 0.1f;
	mesh*     m_mesh = nullptr;
	particle* m_particles = nullptr;
	std::function<void(particle&, float)> m_update_func;

	/// Draw Data
	uint32_t vao = 0;
	uint32_t instanced_vbo = 0;
	shader shader;
};

