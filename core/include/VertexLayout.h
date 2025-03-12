#pragma once
#include <vector>

class VertexLayout
{
public:
	struct VertexAttribute
	{
		int  location;
		int  count;
		int  type;
		bool normalized;
		int  offset = 0; 
	};

public:
	VertexLayout(std::initializer_list<VertexAttribute> attributes);

	inline uint32_t get_vertex_stride() const
	{
		return m_vertex_stride;
	}

	std::vector<VertexAttribute>::iterator begin() { return m_attributes.begin(); }
	std::vector<VertexAttribute>::iterator end() { return m_attributes.end(); }

	std::vector<VertexAttribute>::const_iterator begin() const { return m_attributes.begin(); }
	std::vector<VertexAttribute>::const_iterator end() const { return m_attributes.end(); }

private:
	void create_layout();

private:
	std::vector<VertexAttribute> m_attributes;
	uint32_t m_vertex_stride = 0;
};

