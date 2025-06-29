#include "vertex_buffer.h"

#include <vector>
#include <GL/glew.h>

vertex_buffer::vertex_buffer()
{
	glGenBuffers(1, &m_id);
}

vertex_buffer::~vertex_buffer()
{
	glDeleteBuffers(1, &m_id);
}

void vertex_buffer::upload_data(const std::vector<float>& vertices)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
	unbind();
}

void vertex_buffer::upload_data(const std::vector<face>& faces)
{
	bind();
	uint32_t bytes = sizeof(faces[0]) * faces.size();
	glBufferData(GL_ARRAY_BUFFER, bytes, faces.data(), GL_STATIC_DRAW);
	unbind();
}

void vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void vertex_buffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
