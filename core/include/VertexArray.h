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
	void complete_setup(std::unique_ptr<VertexBuffer> buffer, const VertexLayout& layout);

private:
	uint32_t m_id = 0;
	std::unique_ptr<VertexBuffer> m_vbo = nullptr;
};

