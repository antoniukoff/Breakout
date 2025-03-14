#include <GL/glew.h>

#include "Renderer.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"

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

	current_material = nullptr;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::submit(Material* material, Mesh* mesh, const mat4& model_matrix)
{
	if (&current_material != &material)
	{
		material->set_mat("view_matrix", m_view_matrix);
		material->set_mat("projection_matrix", m_projection_matrix);
		current_material = material;
	}
	material->set_mat("model_matrix", model_matrix);

	material->bind();
	mesh->bind();
	glDrawArrays(GL_TRIANGLES, 0, mesh->get_vertex_count());
}

void Renderer::end_frame()
{
}
