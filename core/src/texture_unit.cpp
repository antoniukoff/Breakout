#include "texture_unit.h"
#include "gl_utils.h"

texture_unit::texture_unit()
{
	m_texture_types.resize(3);
	std::fill(m_texture_types.begin(), m_texture_types.end(), EMPTY_TEXTURE_ID);
}

bool texture_unit::has_bound_texture(int texture_type, int texture_id /* = EMPTY_TEXTURE_INDE*/) const
{
	return m_texture_types[gl_utils::get_texture_type(texture_type)] == texture_id;
}

void texture_unit::assign_texture(int texture_type, int texture_id)
{
	m_texture_types[gl_utils::get_texture_type(texture_type)] = texture_id;
}

