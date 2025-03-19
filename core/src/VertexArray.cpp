#include "VertexArray.h"
#include <gl/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::complete_setup(VertexBuffer* buffer, const VertexLayout& layout)
{
	bind();
	buffer->bind();

	uint32_t vertex_stride = layout.get_vertex_stride();
	for (auto& attribute : layout)
	{
		glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized, vertex_stride, (void*)attribute.offset);
		glEnableVertexAttribArray(attribute.location);
	}
	unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}


