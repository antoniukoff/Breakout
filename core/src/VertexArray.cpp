#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

void VertexArray::set_vbo(const VertexBuffer& vbo, const VertexLayout& layout)
{
	bind();
	vbo.bind();
	layout.enable_attributes();
	unbind();
}

void VertexArray::bind()
{
	glBindVertexArray(m_id);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}
