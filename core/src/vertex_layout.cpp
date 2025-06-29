#include "vertex_layout.h"
#include "gl_utils.h"
#include <iostream>
#include <algorithm>


vertex_layout::vertex_layout(std::initializer_list<vertex_attribute> attributes)
	: m_attributes(attributes)
{
	create_layout();
}

void vertex_layout::create_layout()
{
	std::sort(m_attributes.begin(), m_attributes.end(), [](const vertex_attribute& a1, const vertex_attribute& a2)
		{
			return a1.location < a2.location;
		});

	int offset = 0;

	for (auto& attribute : m_attributes)
	{
		attribute.offset = offset;

		uint32_t attribute_size = attribute.count * gl_utils::gl_type_to_cpp_size(attribute.type);
		offset			+= attribute_size;
		m_vertex_stride += attribute_size;
	}
}
