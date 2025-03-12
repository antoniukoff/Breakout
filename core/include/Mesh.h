#pragma once
#include "math/mat4.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include <string>

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
	std::unique_ptr<VertexArray> m_vao = nullptr;
	uint32_t m_vertex_count = 0;
};

