#include "VertexLayout.h"
#include "Utility.h"
#include <iostream>
#include <algorithm>

VertexLayout::VertexLayout(const std::vector<VertexAttribute> attributes)
	: m_attributes(attributes)
{
	create_layout();
}

void VertexLayout::create_layout()
{
	std::sort(m_attributes.begin(), m_attributes.end(), [](const VertexAttribute& a1, const VertexAttribute& a2)
		{
			return a1.location < a2.location;
		});

	int offset = 0;

	for (auto& attribute : m_attributes)
	{
		attribute.offset = offset;

		unsigned int attribute_size = attribute.count * gl_utils::gl_type_to_cpp_size(attribute.type);
		offset += attribute_size;
		stride += attribute_size;
	}
}

void VertexLayout::enable_attributes() const
{
	for (auto& attribute : m_attributes)
	{
		glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized, stride, (void*)attribute.offset);
		glEnableVertexAttribArray(attribute.location);
	}
}
