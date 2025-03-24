#include "ParticleBatch.h"
#include "Mesh.h"
#include "GL/glew.h"
#include "Shader.h"
#include "Camera.h"

struct RenderData
{
	mat4 model;
	Color color;
};

ParticleBatch::ParticleBatch()
	: shader("assets/shaders/particle.glsl")
{}

ParticleBatch::~ParticleBatch()
{
	delete[] m_particles;
	glDeleteBuffers(1, &instanced_vbo);
	glDeleteVertexArrays(1, &vao);
}

void ParticleBatch::initizalize(uint32_t max_particles, float decay_rate, Mesh* mesh, std::function<void(Particle&, float dt)> update_func)
{
	if (m_particles)
	{
		delete[] m_particles;
	}

	m_particles = new Particle[max_particles];
	m_size = 0;
	m_mesh = mesh;
	m_max_marticles = max_particles;
	m_decay_rate = decay_rate;
	m_update_func = update_func;
	
	if (!m_initialized)
	{
		glDeleteBuffers(1, &instanced_vbo);
		glDeleteVertexArrays(1, &vao);
	}
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &instanced_vbo);

	glBindVertexArray(vao);

	mesh->get_vbo().bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//// Configuring attributes to send mat4 per instance
	//// Max attribute size to send to the gpu is vec4
	//// So we send matrix as 4 vec4's to the vertex shader 
	glBindBuffer(GL_ARRAY_BUFFER, instanced_vbo);
	glBufferData(GL_ARRAY_BUFFER, max_particles * sizeof(RenderData), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(RenderData), (void*)0);
	glVertexAttribDivisor(1, 1);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(RenderData), (void*)(offsetof(RenderData, model) + sizeof(vec4)));
	glVertexAttribDivisor(2, 1);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(RenderData), (void*)(offsetof(RenderData, model) + sizeof(vec4) * 2));
	glVertexAttribDivisor(3, 1);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(RenderData), (void*)(offsetof(RenderData, model) + sizeof(vec4) * 3));
	glVertexAttribDivisor(4, 1);

	//// Color Data
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(RenderData), (void*)offsetof(RenderData, color));
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);

	m_initialized = true;
}

void ParticleBatch::update(float dt)
{
	for (int i = 0; i < m_size; i++)
	{
		auto& particle = m_particles[i];

		particle.prev_position = particle.position;
		m_update_func(particle, dt);
		particle.life -= m_decay_rate * dt;
		if (particle.life <= 0.0f)
		{
			particle = m_particles[m_size - 1];
			m_size--;
			/// process moved particle
			i--; 
		}
	}
}

void ParticleBatch::draw(Camera& camera, float interval)
{
	shader.bind();
	mat4 view		= camera.get_view_matrix(interval);
	mat4 projection = camera.get_projection_matrix();

	shader.upload_mat4("view", view);
	shader.upload_mat4("projection", projection);

	std::vector<RenderData> instanced_data;

	for (int i = 0; i < m_size; i++)
	{
		auto& p = m_particles[i];
		vec3& position = p.position;
		vec3& prev_position = p.prev_position;
		float scale = p.scale;

		vec3 interpolated_position = prev_position * (1.0f - interval) + position * interval;

		mat4 model = mat4::translate(interpolated_position) * mat4::scale(vec3{ scale, scale, scale });
		Color color = p.color;

		instanced_data.push_back({ model, color });
	}

	//// Upload instance data
	glBindBuffer(GL_ARRAY_BUFFER, instanced_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, instanced_data.size() * sizeof(RenderData), instanced_data.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//// Draw instances
	glBindVertexArray(vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, m_mesh->get_vertex_count(), instanced_data.size());
	glBindVertexArray(0);
}

void ParticleBatch::add_particle(const vec3& position, const vec3& velocity, const Color& color, float width)
{
	if (m_size >= m_max_marticles)
	{
		return;
	}
	auto& p = m_particles[m_size];
	p.life = 1.0f;
	p.position = position;
	p.prev_position = position;
	p.velocity = velocity;
	p.color = color;
	p.scale = width;
	m_size++;
}

void ParticleBatch::reset()
{
	m_size = 0;
}
