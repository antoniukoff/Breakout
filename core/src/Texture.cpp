#include "Texture.h"
#include "Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <algorithm>

Texture::Texture(const std::string& file_name, unsigned int type)
	: m_type(type)
{
	load_texture(file_name);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::load_texture(const std::string& file_name)
{
	glGenTextures(1, &m_id);
	glBindTexture(m_type, m_id);
	glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width = 0;
	int height = 0;
	int n_channels = 0;
	unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &n_channels, 0);
	if (!data)
	{
	    glDeleteTextures(1, &m_id);
	}
	
	glTexImage2D(m_type, 0, GL_RGB, width, height, 0, n_channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(m_type);
	
	glBindTexture(m_type, 0);
	stbi_image_free(data);
}


