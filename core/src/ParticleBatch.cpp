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

void ParticleBatch::initizalize(uint32_t max_particles, float decay_rate, Mesh* mesh, std::function<void(Particle&)> update_func)
{
	if (!m_particles)
	{
		m_particles = new Particle[max_particles];
	}
	m_size = 0;
	m_mesh = mesh;
	m_max_marticles = max_particles;
	m_decay_rate = decay_rate;
	m_update_func = update_func;

	if (m_instanciated)
	{
		return;
	}

	int mesh_vertices = mesh->get_vertex_count();
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &instanced_vbo);

	glBindVertexArray(vao);

	//// Mesh data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh_vertices * sizeof(vec3), mesh->get_mesh_positions().data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, instanced_vbo);
	glBufferData(GL_ARRAY_BUFFER, max_particles * sizeof(RenderData), nullptr, GL_DYNAMIC_DRAW);

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

	m_instanciated = true;
}

void ParticleBatch::update()
{
	for (int i = 0; i < m_size; i++)
	{
		auto& particle = m_particles[i];

		particle.prev_position = particle.position;
		m_update_func(particle);
		particle.life -= m_decay_rate;
		if (particle.life <= 0.0f)
		{
			particle = m_particles[m_size - 1];
			m_size--;
			i--; /// process moved particle
		}
	}
}

void ParticleBatch::draw(Camera& camera, float interval)
{
	shader.bind();
	mat4 view = camera.get_view_matrix();
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

		mat4 model = mat4::translate(position) * mat4::scale(vec3{ scale, scale, scale });
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
	p.velocity = velocity;
	p.color = color;
	p.scale = width;
	m_size++;
}
