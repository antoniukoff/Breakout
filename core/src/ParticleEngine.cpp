#include "ParticleEngine.h"
#include "ParticleBatch.h"
#include "Camera.h"

ParticleEngine::ParticleEngine()
	: shader("assets/shaders/particle.glsl")
{
}

ParticleEngine::~ParticleEngine()
{
	for (auto& b : m_partile_batches) {
		delete b;
	}
}

void ParticleEngine::add_particle_batch(ParticleBatch* particleBatch)
{
	m_partile_batches.push_back(particleBatch);
}

void ParticleEngine::update()
{
	for (auto& b : m_partile_batches) {
		b->update();
	}
}

void ParticleEngine::draw(Camera& camera)
{
	for (auto& b : m_partile_batches) {
		b->draw(camera, shader);
	}
}
