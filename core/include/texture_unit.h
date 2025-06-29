#pragma once
#include <vector>

class texture_unit
{
public:
	texture_unit();
	bool has_bound_texture(int texture_type, int texture_id = -1) const;
	void assign_texture(int texture_type, int texture_id);
private:
	std::vector<unsigned int> m_texture_types;
};

