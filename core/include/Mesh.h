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
	Mesh(const std::vector<float> data);
	Mesh(Mesh&& other) noexcept;

	Mesh& operator=(Mesh&& other) noexcept;

	void bind() const;
	void unbind() const;

	uint32_t get_vertex_count() const;
private:
	void parse_obj(const std::string& file_path);
	Face process_face(const std::vector<std::string>& faces_info, const std::vector<vec3>& positions, const std::vector<vec2>& uvs, const std::vector<vec3>& normals);
	void create_mesh(const std::vector<Face>& faces, uint32_t usage_mode);
private:
	std::unique_ptr<VertexArray> m_vao = nullptr;
	uint32_t m_vertex_count = 0;
};

