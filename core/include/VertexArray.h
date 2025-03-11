#pragma once
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();

	void set_vbo(const VertexBuffer& vbo);

	void bind();

	void unbind();

private:
	VertexBuffer vbo;
	unsigned int m_id = 0;
};

