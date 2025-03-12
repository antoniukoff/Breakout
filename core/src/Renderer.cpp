#include "Renderer.h"

#include <GL/glew.h>

Renderer::Renderer()
{
	glClearColor(0.23f, 0.21f, 0.34f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
}

void Renderer::begin_frame(Camera& camera)
{
	m_view_matrix		= camera.get_view_matrix();
	m_projection_matrix = camera.get_projection_matrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::submit(const Shader& shader, const Mesh& mesh, std::vector<mat4> model_matrix)
{
	shader.bind();
	shader.upload_mat4("view_matrix", m_view_matrix);
	shader.upload_mat4("projection_matrix", m_projection_matrix);
	mesh.bind();
	for (int i = 0; i < model_matrix.size(); i++)
	{
		shader.upload_mat4("model_matrix", model_matrix[i]);
		glDrawArrays(GL_TRIANGLES, 0, mesh.get_vertex_count());
	}
	mesh.unbind();
}

void Renderer::end_frame()
{
}
