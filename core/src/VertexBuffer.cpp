#include "VertexBuffer.h"

#include <vector>
#include <GL/glew.h>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_id);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::upload_data(const std::vector<float>& vertices)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
	unbind();
}

void VertexBuffer::upload_data(const std::vector<Face>& faces)
{
	bind();
	uint32_t bytes = sizeof(faces[0]) * faces.size();
	glBufferData(GL_ARRAY_BUFFER, bytes, faces.data(), GL_STATIC_DRAW);
	unbind();
}


void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
