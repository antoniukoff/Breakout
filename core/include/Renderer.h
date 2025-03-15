#pragma once
#include "math/vec3.h"
#include "math/mat4.h"
#include <memory>

class Camera;
class Mesh;
class Material;

class Renderer
{
public:
	static void initialize(vec3 clear_color, bool enable_depth_test = true, bool enable_face_culling = true);

	static void begin_frame(Camera& camera);
	static void submit(Material* material, Mesh* mesh, const mat4& model_matrix);
	static void end_frame();

private:
	static mat4 m_view_matrix;
	static mat4 m_projection_matrix;
	static Material* current_material;

	static std::unique_ptr<Renderer> s_instance;
};

