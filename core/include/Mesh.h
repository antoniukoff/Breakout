#pragma once
#include "math/mat4.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include <string>
#include "math/vec2.h"

class mesh
{
public:
	mesh() = default;
	mesh(const std::string& file_path);

	void bind() const;
	void unbind() const;

	uint32_t get_vertex_count() const;

	vertex_buffer& get_vbo()
	{
		return m_vbo;
	}

private:
	void parse_obj(const std::string& file_path);
	face process_face(const std::vector<std::string>& faces_info, const std::vector<vec3>& positions, const std::vector<vec2>& uvs, const std::vector<vec3>& normals);
	void create_mesh(const std::vector<face>& faces, uint32_t usage_mode);

private:
	vertex_array m_vao;
	vertex_buffer m_vbo;

	uint32_t m_vertex_count = 0;
};

