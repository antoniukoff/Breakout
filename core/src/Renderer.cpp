#include <GL/glew.h>

#include "Renderer.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"

mat4 Renderer::m_view_matrix;
mat4 Renderer::m_projection_matrix;
Material* Renderer::current_material = nullptr;

void Renderer::initialize(vec3 clear_color, bool enable_depth_test, bool enable_face_culling)
{
	glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
	
	if (enable_depth_test)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	if (enable_face_culling)
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::begin_frame(Camera& camera, float interval)
{
	m_view_matrix		= camera.get_view_matrix(interval);
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
	//// Create draw batches to minimize shader change, then flush
}
