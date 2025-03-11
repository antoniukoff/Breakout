#include "VertexBuffer.h"

#include <vector>
#include <GL/glew.h>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_id);
}

void VertexBuffer::upload_data(const std::vector<float>& vertices)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
	unbind();
}

void VertexBuffer::set_layout(const VertexLayout& layout)
{
	m_layout = layout;
}

void VertexBuffer::enable_layout() const
{
	m_layout.enable_attributes();
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
