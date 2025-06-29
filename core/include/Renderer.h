#pragma once
#include "math/vec3.h"
#include "math/mat4.h"
#include <memory>

class camera;
class mesh;
class material;

class renderer
{
public:
	static void initialize(vec3 clear_color, bool enable_depth_test = true, bool enable_face_culling = true);

	/// Renderer states
	static void set_clear_color(vec3 clear_color);

	static void prepare_new_frame();
	static void submit(material* material, mesh* mesh, const mat4& model_matrix);
	static void end_frame();

private:
	static material* current_material;
};

