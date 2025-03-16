#pragma once
#include "math/vec3.h"
#include <functional>
#include "Color.h"

class Camera;
class Mesh;
class Shader;

class Particle {
public:
	vec3 position;
	vec3 velocity;
	Color color;
	float life = 0.0f;
	float scale = 0.0f;	
};

inline void default_particle_update(Particle& particle)
{
	particle.position += particle.velocity;
}

class ParticleBatch
{
public:
	ParticleBatch();
	~ParticleBatch();

	void initizalize(uint32_t max_particles, float decay_rate, Mesh* mesh, std::function<void(Particle&)> update_func = default_particle_update);
	void update();
	void draw(Camera& camera, Shader& shader);
	void add_particle(const vec3& position,
		const vec3& velocity,
		const Color& color,
		float scale);
private:
	//// Particle Data
	int m_size = 0;
	uint32_t m_max_marticles = 0;
	float m_decay_rate = 0.1f;
	Mesh* m_mesh = nullptr;
	Particle* m_particles = nullptr;
	std::function<void(Particle&)> m_update_func;

	/// Draw Data
	uint32_t vao = 0;
	uint32_t instanced_vbo = 0;
	uint32_t vbo = 0;
};

