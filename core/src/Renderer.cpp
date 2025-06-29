#include <GL/glew.h>

#include "renderer.h"
#include "camera.h"
#include "Material.h"
#include "mesh.h"

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

void Renderer::set_clear_color(vec3 clear_color)
{
	glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
}

void Renderer::prepare_new_frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::submit(Material* material, Mesh* mesh, const mat4& model_matrix)
{
	material->set_mat("model_matrix", model_matrix);

	material->bind();
	mesh->bind();
	glDrawArrays(GL_TRIANGLES, 0, mesh->get_vertex_count());
}


void Renderer::end_frame()
{
	//// Create draw batches to minimize shader change, then flush
}
