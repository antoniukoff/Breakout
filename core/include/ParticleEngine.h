#pragma once
#include <vector>
#include "Shader.h"

class Camera;
class ParticleBatch;
class ParticleEngine
{
public:
	ParticleEngine();
	~ParticleEngine();

	//After adding a particle batch , the ParticleEngine becomes 
	//responsible for deallocation
	void add_particle_batch(ParticleBatch* particleBatch);
	void update();
	void draw(Camera& camera);

private:
	Shader shader;
	std::vector<ParticleBatch*> m_partile_batches;
};

