#pragma once
#include "math/mat4.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include <string>
#include "math/vec2.h"

class Mesh
{
public:
	Mesh() = default;
	Mesh(const std::string& file_path);

	void bind() const;
	void unbind() const;

	uint32_t get_vertex_count() const;

	std::vector<vec3>& get_mesh_positions()
	{
		return m_positions;
	}
	std::shared_ptr<VertexBuffer> get_vbo()
	{
		return m_vbo;
	}

private:
	void parse_obj(const std::string& file_path);
	Face process_face(const std::vector<std::string>& faces_info, const std::vector<vec3>& positions, const std::vector<vec2>& uvs, const std::vector<vec3>& normals);
	void create_mesh(const std::vector<Face>& faces, uint32_t usage_mode);
private:
	std::vector<vec3> m_positions;
	std::vector<vec2> m_tex_coords;
	std::vector<vec3> m_normals;
	std::shared_ptr<VertexArray> m_vao = nullptr;
	std::shared_ptr<VertexBuffer> m_vbo = nullptr;
	uint32_t m_vertex_count = 0;
};

