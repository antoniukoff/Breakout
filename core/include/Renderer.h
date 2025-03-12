#pragma once
#include "math/mat4.h"
#include "TextureUnit.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();

	void begin_frame(Camera& camera);
	void submit(const Shader& shader, const Mesh& mesh, std::vector<mat4> model_matrix);
	void end_frame();

private:
private:
	std::vector<TextureUnit> m_texture_units;

	mat4 m_view_matrix;
	mat4 m_projection_matrix;
};

