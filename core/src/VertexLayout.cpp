#include "VertexLayout.h"
#include <algorithm>

void VertexLayout::create_layout(std::vector<VertexAttibute>&& attributes)
{
	std::sort(attributes.begin(), attributes.end(), [](const VertexAttibute& a1, const VertexAttibute& a2)
		{
			return a1.location < a2.location;
		});

	int total_bytes = 0;

	for (const auto& attribute : attributes)
	{
		void* stride = (void*)(total_bytes);

		VertexAttibute a = {
			.location = attribute.location,
			.count = attribute.count,
			.type = attribute.type,
			.normalized = attribute.normalized,
			.stride = stride
		};

		m_attributes.push_back(a);
		unsigned int attribute_size = attribute.count * gl_utils::gl_type_to_cpp_size(attribute.type);
		total_bytes += attribute_size;
		byte_offset += attribute_size;
	}
}

void VertexLayout::enable_attributes() const
{
	for (auto& attribute : m_attributes)
	{
		glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized, byte_offset, attribute.stride);
		glEnableVertexAttribArray(attribute.location);
	}
}
