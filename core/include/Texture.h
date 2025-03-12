#pragma once
#include <vector>
#include <string>
#include <GL/glew.h>
#include "TextureUnit.h"

class Texture
{
public:
	Texture(const std::string& file_name, unsigned int type);
	~Texture();

	inline const unsigned int get_type() const
	{
		return m_type;
	}

	inline const unsigned int get_id() const
	{
		return m_id;
	}

private:
	void load_texture(const std::string& file_name);

private:
	unsigned int m_type = GL_TEXTURE_2D;
	unsigned int m_id = 0;
};

