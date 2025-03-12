#include "Mesh.h"
#include <memory>
#include <gl/glew.h>


Mesh::Mesh(const std::string& file_path)
{
}

Mesh::Mesh(const std::vector<float> data)
{
	m_vao = std::make_unique<VertexArray>();

	/// Create VBO
	std::unique_ptr<VertexBuffer> buffer = std::make_unique<VertexBuffer>();
	buffer->upload_data(data);

	/// Create Layout
	VertexLayout layout = {
		{0, 3, GL_FLOAT, GL_FALSE},
		{1, 2, GL_FLOAT, GL_FALSE},
		{2, 1, GL_FLOAT, GL_FALSE}
	};

	m_vertex_count = buffer->get_attribute_count() * sizeof(float) / layout.get_vertex_stride();

	/// Set VBO and Layout to VAO
	m_vao->complete_setup(std::move(buffer), layout);
}

Mesh::Mesh(Mesh&& other) noexcept
	: m_vao(std::move(other.m_vao))
	, m_vertex_count(other.m_vertex_count)
{
	other.m_vertex_count = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this != &other)
	{
		m_vao = std::move(other.m_vao);
		m_vertex_count = other.m_vertex_count;

		other.m_vertex_count = 0;
	}
	return *this;
}

void Mesh::bind() const
{
	m_vao->bind();
}

void Mesh::unbind() const
{
	m_vao->unbind();
}

uint32_t Mesh::get_vertex_count() const
{
	return m_vertex_count;
}

