#include "vertex_array.h"
#include <gl/glew.h>

vertex_array::vertex_array()
{
	glGenVertexArrays(1, &m_id);
}

vertex_array::~vertex_array()
{
	glDeleteVertexArrays(1, &m_id);
}

void vertex_array::complete_setup(const vertex_buffer& buffer, const vertex_layout& layout)
{
	bind();
	buffer.bind();

	uint32_t vertex_stride = layout.get_vertex_stride();
	for (auto& attribute : layout)
	{
		glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized, vertex_stride, (void*)attribute.offset);
		glEnableVertexAttribArray(attribute.location);
	}
	unbind();
}

void vertex_array::bind() const
{
	glBindVertexArray(m_id);
}

void vertex_array::unbind() const
{
	glBindVertexArray(0);
}


