#include "TextureUnit.h"
#include "GLUtils.h"

TextureUnit::TextureUnit()
{
	m_texture_types.resize(3);
	std::fill(m_texture_types.begin(), m_texture_types.end(), EMPTY_TEXTURE_ID);
}

bool TextureUnit::has_bound_texture(int texture_type, int texture_id /* = EMPTY_TEXTURE_INDE*/) const
{
	return m_texture_types[gl_utils::get_texture_type(texture_type)] == texture_id;
}

void TextureUnit::assign_texture(int texture_type, int texture_id)
{
	m_texture_types[gl_utils::get_texture_type(texture_type)] = texture_id;
}

