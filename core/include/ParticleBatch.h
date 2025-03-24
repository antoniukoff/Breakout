#pragma once
#include "math/vec3.h"
#include <functional>
#include "Color.h"
#include "Shader.h"

class Mesh;
class Camera;

class Particle 
{
public:
	vec3 position;
	vec3 prev_position;
	vec3 velocity;
	Color color;
	float life = 0.0f;
	float scale = 0.0f;	
};

inline void default_particle_update(Particle& particle, float dt)
{
	const float gravity = 115; 

	particle.velocity.z -= gravity * dt;
	particle.prev_position = particle.position;
	particle.position += particle.velocity * dt;

	particle.color.a = (unsigned char)(particle.life * 255.0f);
}

class ParticleBatch
{
public:
	ParticleBatch();
	~ParticleBatch();

	void initizalize(uint32_t max_particles, float decay_rate, Mesh* mesh, std::function<void(Particle&, float)> update_func = default_particle_update);
	void update(float dt);
	void draw(Camera& camera, float interval);
	void add_particle(const vec3& position,
		const vec3& velocity,
		const Color& color,
		float scale);

	void reset();

	inline uint32_t get_capacity() const { return m_max_marticles; }

private:
	//// Particle Data
	bool	  m_initialized = false;
	uint32_t  m_size = 0;
	uint32_t  m_max_marticles = 0;
	float	  m_decay_rate = 0.1f;
	Mesh*     m_mesh = nullptr;
	Particle* m_particles = nullptr;
	std::function<void(Particle&, float)> m_update_func;

	/// Draw Data
	uint32_t vao = 0;
	uint32_t instanced_vbo = 0;
	Shader shader;
};

