#pragma once
#include <vector>
#include <gl/glew.h>

struct VertexLayout
{
	struct VertexAttribute
	{
		int  location;
		int  count;
		int  type;
		bool normalized;
		int  offset = 0; 
	};

public:
	VertexLayout(const std::vector<VertexAttribute> attributes);
	void enable_attributes() const;

private:
	void create_layout();

private:
	std::vector<VertexAttribute> m_attributes;
	unsigned int stride = 0;
};

