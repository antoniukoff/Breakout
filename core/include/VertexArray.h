#pragma once
#include "VertexBuffer.h"
#include <memory>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;
	void complete_setup(const VertexBuffer& buffer, const VertexLayout& layout);

private:
	uint32_t m_id = 0;
};

