#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

void VertexArray::set_vbo(const VertexBuffer& vbo)
{
	this->vbo = vbo;

	bind();
	vbo.bind();
	vbo.enable_layout();
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
