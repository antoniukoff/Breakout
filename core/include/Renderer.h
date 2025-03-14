#pragma once
#include "math/mat4.h"

class Camera;
class Mesh;
class Material;

class Renderer
{
public:
	Renderer();

	void begin_frame(Camera& camera);
	void submit(Material* material, Mesh* mesh, const mat4& model_matrix);
	void end_frame();

private:

	mat4 m_view_matrix;
	mat4 m_projection_matrix;

	Material* current_material = nullptr;
};

