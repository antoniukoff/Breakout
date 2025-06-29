#pragma once
#include <vector>

class vertex_layout
{
public:
	struct vertex_attribute
	{
		int  location;
		int  count;
		int  type;
		bool normalized;
		int  offset = 0; 
	};

public:
	vertex_layout(std::initializer_list<vertex_attribute> attributes);

	inline uint32_t get_vertex_stride() const
	{
		return m_vertex_stride;
	}

	std::vector<vertex_attribute>::iterator begin() { return m_attributes.begin(); }
	std::vector<vertex_attribute>::iterator end() { return m_attributes.end(); }

	std::vector<vertex_attribute>::const_iterator begin() const { return m_attributes.begin(); }
	std::vector<vertex_attribute>::const_iterator end() const { return m_attributes.end(); }

private:
	void create_layout();

private:
	std::vector<vertex_attribute> m_attributes;
	uint32_t m_vertex_stride = 0;
};

