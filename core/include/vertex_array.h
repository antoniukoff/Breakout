#pragma once
#include "vertex_buffer.h"
#include <memory>

class vertex_array
{
public:
	vertex_array();
	~vertex_array();

	void bind() const;
	void unbind() const;
	void complete_setup(const vertex_buffer& buffer, const vertex_layout& layout);

private:
	uint32_t m_id = 0;
};

