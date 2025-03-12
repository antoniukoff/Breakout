#pragma once
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();

	void bind();
	void unbind();
	void set_vbo(const VertexBuffer& vbo, const VertexLayout& layout);
private:
	unsigned int m_id = 0;
};

